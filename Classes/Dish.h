#ifndef DISH_H
#define DISH_H

#include <chrono>
#include "Recipe.h"

class Dish {
private:
    Recipe recipe;
    int customer;
    std::chrono::high_resolution_clock::time_point timer;

public:
    Dish();
    Dish(Recipe recipe, int customer);
    Dish(const Dish& other);
    void setTimer(double duration);
    bool checkIfReady();
    const Recipe& getRecipe() const;
    int getCustomer() const;
    Dish& operator=(const Dish& other);
    bool empty() const;
};

#endif