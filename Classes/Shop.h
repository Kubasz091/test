#ifndef SHOP_H
#define SHOP_H

#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include "Ingredient.h"

class Shop {
private:
    std::vector<Ingredient> ingredients;
    int totalSpent;

public:
    Shop();
    void addIngredient(std::string name, int price);
    int buyIngredient(std::string name, int quantity);
    int getIngredientPrice(std::string name);
    Ingredient getIngredient(std::string name);
    int getTotalSpent();
};

#endif