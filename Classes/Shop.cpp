#include "Shop.h"

Shop::Shop() : totalSpent(0) {}

void Shop::addIngredient(std::string name, int price) {
    ingredients.push_back(Ingredient(name, price));
}

int Shop::buyIngredient(std::string name, int quantity) {
    for (auto& ingredient : ingredients) {
        if (ingredient.getName() == name) {
            int cost = ingredient.getCost() * (quantity/100.0);
            totalSpent += cost;
            return cost;
        }
    }
    throw std::runtime_error("Ingredient not found in shop");
}

Ingredient Shop::getIngredient(std::string name) {
    for (const auto& ingredient : ingredients) {
        if (ingredient.getName() == name) {
            return ingredient;
        }
    }
    throw std::runtime_error("Ingredient not found in shop");
}

int Shop::getIngredientPrice(std::string name) {
    for (const auto& ingredient : ingredients) {
        if (ingredient.getName() == name) {
            return ingredient.getCost();
        }
    }
    throw std::runtime_error("Ingredient not found in shop");
}

int Shop::getTotalSpent() {
    return totalSpent;
}