#include "Dish.h"

Dish::Dish() : recipe(Recipe("", {})), customer(0) {}

Dish::Dish(Recipe recipe, int customer)
    : recipe(recipe), customer(customer) {}

Dish::Dish(const Dish& other)
    : recipe(other.recipe), customer(other.customer), timer(other.timer) {}

void Dish::setTimer(double duration) {
    auto duration_in_seconds = std::chrono::duration<double>(duration);
    auto high_res_duration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration_in_seconds);

    timer = std::chrono::high_resolution_clock::now() + high_res_duration;
}

bool Dish::checkIfReady() {
    return std::chrono::high_resolution_clock::now() >= timer;
}

const Recipe& Dish::getRecipe() const {
    return recipe;
}

int Dish::getCustomer() const {
    return customer;
}

Dish &Dish::operator=(const Dish &other) {
    if (this == &other) {
        return *this;
    }
    recipe = other.recipe;
    customer = other.customer;
    timer = other.timer;
    return *this;
}

bool Dish::empty() const {
    return recipe.getName().empty() && customer == 0;
}