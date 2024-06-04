#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include "Ingredient.h"

struct IngredientQuantity {
    Ingredient ingredient;
    int quantity;
    IngredientQuantity& operator = (const IngredientQuantity& ingredientQuantity) {
        if (this == &ingredientQuantity) {
            return *this;
        }
        ingredient = ingredientQuantity.ingredient;
        quantity = ingredientQuantity.quantity;
        return *this;
    }
    IngredientQuantity(const Ingredient& ingredient, int quantity)
        : ingredient(ingredient), quantity(quantity) {}
};

class Recipe {
private:
    std::string name;
    std::vector<IngredientQuantity> ingredients;
public:
    Recipe(std::string name, std::vector<IngredientQuantity> ingredients);
    Recipe(const Recipe& other); // Copy constructor
    int calculateCost() const;
    const std::string& getName() const;
    const std::vector<IngredientQuantity>& getIngredients() const;
    Recipe& operator = (const Recipe& recipe);
};

#endif