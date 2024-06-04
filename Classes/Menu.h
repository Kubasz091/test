#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include <stdexcept>
#include "Recipe.h"

struct MenuPosition {
    Recipe recipe;
    int price;
    MenuPosition(const Recipe& recipe, int price)
        : recipe(recipe), price(price) {}
};

class Menu {
private:
    std::vector<MenuPosition> dishes;
public:
    void addRecipe(Recipe recipe, const int price);
    int getPrice(const std::string& dishName) const;
    const Recipe& getRecipe(const std::string& dishName) const;
    std::vector<MenuPosition> getDishes() const;
};

#endif