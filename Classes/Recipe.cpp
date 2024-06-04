#include "Recipe.h"

Recipe::Recipe(std::string name, std::vector<IngredientQuantity> ingredients)
    : name(std::move(name)), ingredients(std::move(ingredients)) {}

Recipe::Recipe(const Recipe& other)
    : name(other.name), ingredients(other.ingredients) {}

int Recipe::calculateCost() const {
    int cost = 0;
    for (const auto& ingredientQuantity : ingredients) {
        cost += ingredientQuantity.ingredient.getCost() * ingredientQuantity.quantity;
    }
    return cost;
}

const std::string& Recipe::getName() const {
    return name;
}

const std::vector<IngredientQuantity>& Recipe::getIngredients() const {
    return ingredients;
}

Recipe &Recipe::operator=(const Recipe& new_recipe) {
    if (this == &new_recipe) {
        return *this;
    }
    name = new_recipe.name;
    ingredients = new_recipe.ingredients;
    return *this;
}