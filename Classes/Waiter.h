#ifndef WAITER_H
#define WAITER_H

#include <chrono>
#include "Customer.h"
#include "Dish.h"

class Waiter {
private:
    int customer = 0;
    bool customer_paying = false;
    Dish dish;
    std::chrono::time_point<std::chrono::high_resolution_clock> timer;
public:
    void takeOrderFromCustomer(int customerId);
    void takeDish(Dish newDish);
    int getCurrentCustomer();
    Dish getCurrentDish();
    void setTimer(double duration);
    bool checkIfReady() const;
    void setCustomerPaying(bool paying);
    bool getCustomerPaying() const;
    bool haveDish() const;
    bool haveCustomer() const;
};
#endif