#include <iostream>
#include <random>
#include "spdlog/spdlog.h"
#include "Restaurant.h"

Restaurant::Restaurant( int num_Cooks, int starting_money, int duration_in_minutes) : kitchen(num_Cooks, starting_money) {
    auto duration_in_seconds = std::chrono::duration<double>(clientSpawnDelay);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);
    timerNextCustomer = std::chrono::high_resolution_clock::now() + high_res_duration;

    auto duration_in_seconds2 = std::chrono::duration<double>(duration_in_minutes * 60);
    auto high_res_duration2 = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds2);
    timerEndSimulation = std::chrono::high_resolution_clock::now() + high_res_duration2;
}

void Restaurant::setParameters(double clientSpawnDelay, double orderPrepareDelay, double waiterWalkDelay, double customerEatDelay, double customerOrderDelay) {
    this->clientSpawnDelay = clientSpawnDelay;
    this->orderPrepareDelay = orderPrepareDelay;
    this->waiterWalkDelay = waiterWalkDelay;
    this->customerEatDelay = customerEatDelay;
    this->customerOrderDelay = customerOrderDelay;
}

void Restaurant::spawnCustomer() {
    for (auto& table : tables) {
        if (!table.isOccupied()) {
            Customer customer(customers_spawned);
            customers_spawned++;
            table.seatCustomer(customer);
            customersWaitingForOrder.push_back(customer);
            customers.push_back(customer);
            customer.setTimer(customerOrderDelay);
            spdlog::info("Customer {} spawned, gonna order in {} seconds", customer.getId(), customerOrderDelay);
            break;
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.7, 1.3);
    auto time_step = clientSpawnDelay;
    time_step *= dis(gen);
    auto duration_in_seconds = std::chrono::duration<double>(time_step);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);
    timerNextCustomer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

void Restaurant::addWaiter(const Waiter& waiter) {
    waiters.push_back(waiter);
}

void Restaurant::addTable(const Table& table) {
    tables.push_back(table);
}

void Restaurant::addRecipeToMenu(const Recipe& recipe, int price) {
    menu.addRecipe(recipe, price);
}

Kitchen& Restaurant::getKitchen() {
    return kitchen;
}

bool Restaurant::endSimulation() {
    return std::chrono::high_resolution_clock::now() >= timerEndSimulation;
}

void Restaurant::handleLogic() {
    if (timerNextCustomer <= std::chrono::high_resolution_clock::now()) {
        spawnCustomer();
    }

    if (!ordersToServe.empty()) {
        for (auto& waiter : waiters) {
            if (!waiter.haveDish() && waiter.checkIfReady() && !waiter.haveCustomer() && !ordersToServe.empty()) {
                Dish& dish = ordersToServe.front();
                waiter.takeDish(dish);
                ordersToServe.pop();
                waiter.setTimer(waiterWalkDelay);
                waiter.setCustomerPaying(false);
                spdlog::info("Waiter walking towards customer {} with order: {}", dish.getCustomer(), dish.getRecipe().getName());
                break;
            }
        }
    }

    for (auto it = customersWaitingForOrder.begin(); it != customersWaitingForOrder.end();) {
        if (it->checkIfReady()) {
            for (auto& waiter : waiters) {
                if (!waiter.haveDish() && waiter.checkIfReady() && !waiter.haveCustomer()) {
                    waiter.takeOrderFromCustomer(it->getId());
                    waiter.setTimer(waiterWalkDelay);
                    waiter.setCustomerPaying(false);
                    spdlog::info("Waiter walking to customer {} to take order", it->getId());
                    it = customersWaitingForOrder.erase(it);
                    break;
                }
            }
        } else {
            ++it;
        }
    }

    for (auto it = customersWaitingToPay.begin(); it != customersWaitingToPay.end();) {
        if (it->checkIfReady()) {
            for (auto& waiter : waiters) {
                if (!waiter.haveDish() && waiter.checkIfReady() && !waiter.haveCustomer()) {
                    waiter.takeOrderFromCustomer(it->getId());
                    waiter.setTimer(waiterWalkDelay);
                    waiter.setCustomerPaying(true);
                    spdlog::info("Waiter walking to customer {} to take payment", it->getId());
                    it = customersWaitingToPay.erase(it);
                    break;
                }
            }
        } else {
            ++it;
        }
    }

    for (Waiter& waiter : waiters) {
        if ((waiter.haveDish() || waiter.haveCustomer()) && waiter.checkIfReady()) {
            if (waiter.haveCustomer()) {
                auto customerIt = std::find_if(customers.begin(), customers.end(), [&waiter](const Customer& c) {
                    return c.getId() == waiter.getCurrentCustomer();
                });
                if (customerIt != customers.end()) {
                    Customer& customer = *customerIt;

                    if (!waiter.haveDish() && !waiter.getCustomerPaying()) {
                        auto order = customer.order(menu);
                        Dish dish(order.recipe, customer.getId());
                        ordersToMake.push(dish);
                        spdlog::info("Customer {} ordered: {}", customer.getId(), dish.getRecipe().getName());
                        waiter.takeOrderFromCustomer(0);
                    }
                    else if (!waiter.haveDish() && waiter.getCustomerPaying()) {
                        kitchen.getAccount().deposit(customer.pay());
                        spdlog::info("Customer {} paid", customer.getId());
                        customers.erase(customerIt);
                        auto tableIt = std::find_if(tables.begin(), tables.end(), [&customer](Table& table) {
                            return table.getCustomer() == customer;
                        });
                        if (tableIt != tables.end()) {
                            tableIt->removeCustomer();
                        }
                        spdlog::info("Customer left the restaurant");
                        waiter.takeOrderFromCustomer(0);
                    }

                }
                else {
                    spdlog::warn("Customer not found with ID {}", waiter.getCurrentCustomer());
                    waiter.takeOrderFromCustomer(0);
                }
            }
            else if (waiter.haveDish()) {
                auto dish = waiter.getCurrentDish();
                auto customerIt = std::find_if(customers.begin(), customers.end(), [&dish](const Customer& c) {
                    return c.getId() == dish.getCustomer();
                });

                if (customerIt != customers.end()) {
                    Customer& customer = *customerIt;

                    spdlog::info("Waiter served: {}", waiter.getCurrentDish().getRecipe().getName());
                    customersWaitingToPay.push_back(customer);
                    customer.setTimer(customerEatDelay);
                    spdlog::info("Customer {} is eating for {} seconds", customer.getId(), customerEatDelay);
                    waiter.takeDish(Dish());
                }
            }
            }

    }

    if (currentDishPrepearing.empty() && !ordersToMake.empty()) {
        currentDishPrepearing = ordersToMake.front();
        ordersToMake.pop();
        currentDishPrepearing.setTimer(kitchen.prepareDish(currentDishPrepearing.getRecipe(), orderPrepareDelay));
        spdlog::info("Dish {} is being prepared, for {} seconds", currentDishPrepearing.getRecipe().getName(), orderPrepareDelay);
    }
    if (!currentDishPrepearing.empty() && currentDishPrepearing.checkIfReady()) {
        ordersToServe.push(currentDishPrepearing);
        currentDishPrepearing = Dish();
    }
}
