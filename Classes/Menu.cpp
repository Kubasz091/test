#include "Menu.h"

void Menu::addRecipe(Recipe recipe, const int price) {
    dishes.push_back(MenuPosition(std::move(recipe), price));
}

int Menu::getPrice(const std::string& dishName) const {
    auto it = std::find_if(dishes.begin(), dishes.end(), [&dishName](const MenuPosition& position) {
        return position.recipe.getName() == dishName;
    });

    if (it != dishes.end()) {
        return it->price;
    } else {
        throw std::runtime_error("Dish not found in menu");
    }
}

const Recipe& Menu::getRecipe(const std::string& dishName) const {
    auto it = std::find_if(dishes.begin(), dishes.end(), [&dishName](const MenuPosition& position) {
        return position.recipe.getName() == dishName;
    });

    if (it != dishes.end()) {
        return it->recipe;
    } else {
        throw std::runtime_error("Dish not found in menu");
    }
}

std::vector<MenuPosition> Menu::getDishes() const {
    return dishes;
}