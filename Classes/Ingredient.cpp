#include "Ingredient.h"

Ingredient::Ingredient(std::string name, int cost) : name(std::move(name)), cost(cost) {}

const std::string& Ingredient::getName() const {
    return name;
}

int Ingredient::getCost() const {
    return cost;
}

Ingredient& Ingredient::operator=(const Ingredient& new_ingredient) {
    if (this == &new_ingredient) {
        return *this;
    }
    name = new_ingredient.name;
    cost = new_ingredient.cost;
    return *this;
}