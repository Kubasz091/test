#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
private:
    std::string name;
    int cost;
public:
    Ingredient(std::string name, int cost);
    const std::string& getName() const;
    int getCost() const;
    Ingredient& operator=(const Ingredient& ingredient);
};

#endif