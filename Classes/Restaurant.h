#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <queue>
#include <iostream>
#include "Customer.h"
#include "Waiter.h"
#include "Menu.h"
#include "Account.h"
#include "Table.h"
#include "Kitchen.h"
#include "Shop.h"

class Restaurant {
private:
    std::vector<Customer> customers;
    std::vector<Customer> customersWaitingForOrder;
    std::vector<Customer> customersWaitingToPay;
    std::vector<Waiter> waiters;
    std::queue<Dish> ordersToMake;
    Dish currentDishPrepearing;
    std::queue<Dish> ordersToServe;
    std::vector<Table> tables;
    std::chrono::time_point<std::chrono::high_resolution_clock> timerNextCustomer;
    std::chrono::time_point<std::chrono::high_resolution_clock> timerEndSimulation;
    Menu menu;
    Kitchen kitchen;
    int customers_spawned = 1;
    double clientSpawnDelay;
    double orderPrepareDelay;
    double waiterWalkDelay;
    double customerEatDelay;
    double customerOrderDelay;

public:
    Restaurant(int num_Cooks, int starting_money, int duration_in_minutes);
    void setParameters(double clientSpawnDelay, double orderPrepareDelay, double waiterWalkDelay, double customerEatDelay, double customerOrderDelay);
    void spawnCustomer();
    void addWaiter(const Waiter& waiter);
    void addTable(const Table& table);
    void addRecipeToMenu(const Recipe& recipe, int price);
    void handleLogic();
    bool endSimulation();
    Kitchen& getKitchen();
};

#endif