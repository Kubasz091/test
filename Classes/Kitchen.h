#ifndef KITCHEN_H
#define KITCHEN_H
#include <chrono>
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"
#include "Shop.h"
#include "Account.h"

class Kitchen {
private:
    int numCooks;
    Shop shop;
    Account account;
public:
    Kitchen(int numCooks, int staring_money);
    double prepareDish(const Recipe& recipe, double normalCookingTime);
    Shop& getShop();
    Account& getAccount();
};

#endif 