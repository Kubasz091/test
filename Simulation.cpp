#include "Simulation.h"
#include "spdlog/spdlog.h"
using json = nlohmann::json;

Simulation::Simulation(int numWaiters, int numCooks, int numTables, int duration, int money)
    : restaurant(numCooks, money, duration), simulationDuration(duration) {
        std::string configFilePath = "../settings.json";
        std::ifstream configFile(configFilePath);
        if (!configFile) {
            throw std::runtime_error("Unable to open config file");
        }
        json config;
        configFile >> config;
        spdlog::info("Opened file settings.json");
        scaleOfTime = config["scaleOfTime"];
        openingTime = config["openingTime"];
        closingTime = config["closingTime"];
        for (auto& element : config["timeSettings"].items()) {
            timeSettings[element.key()] = element.value();
        }
        restaurant.setParameters(timeSettings["clientSpawnDelay"], timeSettings["orderPrepareDelay"], timeSettings["waiterWalkDelay"], timeSettings["customerEatDelay"], timeSettings["customerOrderDelay"]);
        spdlog::info("Set time parameters");
        std::string dataFilePath = "../menu_file.json";
        std::ifstream dataFile(dataFilePath);
        if (!dataFile) {
            throw std::runtime_error("Unable to open data file");
        }
        json data;
        dataFile >> data;
        spdlog::info("Opened file menu_file.json");
        for (auto& element : data["ingredient_prices_per_100g"]) {
            if (!element.contains("name") || !element["name"].is_string() ||
                !element.contains("price") || !element["price"].is_number()) {
                throw std::runtime_error("Error processing ingredient: " + element.dump());
            }
            restaurant.getKitchen().getShop().addIngredient(element["name"], element["price"]);
        }
        for (auto& menuElement : data["menu"]) {
            if (!menuElement.contains("name") || !menuElement["name"].is_string() ||
                !menuElement.contains("price") || !menuElement["price"].is_number()) {
                throw std::runtime_error("Error processing menu element: " + menuElement.dump());
            }
            std::vector<IngredientQuantity> ingredientQuantities;
            for (auto& dishElement : data["dishes"]) {
                if (dishElement["name"] == menuElement["name"]) {
                    for (auto& ingredient : dishElement["ingredients"]) {
                        if (!ingredient.contains("name") || !ingredient["name"].is_string() ||
                            !ingredient.contains("quantity") || !ingredient["quantity"].is_number()) {
                            throw std::runtime_error("Error processing ingredient: " + ingredient.dump());
                        }
                        ingredientQuantities.push_back(IngredientQuantity(restaurant.getKitchen().getShop().getIngredient(ingredient["name"]), ingredient["quantity"]));
                    }
                }
            }
            Recipe recipe(menuElement["name"], ingredientQuantities);
            restaurant.addRecipeToMenu(recipe, menuElement["price"]);
        }

        spdlog::info("Added recipes to menu");

        for (int i = 0; i < numWaiters; i++) {
            Waiter waiter;
            restaurant.addWaiter(waiter);
        }
        for (int i = 0; i < numTables; i++) {
            Table table;
            restaurant.addTable(table);
        }

    }

void Simulation::run() {
    while (!restaurant.endSimulation()) {
         restaurant.handleLogic();
    }
    spdlog::info("Simulation ended");
    spdlog::info("Total money spent: {}", restaurant.getKitchen().getShop().getTotalSpent());
    spdlog::info("Bank ballance: {}", restaurant.getKitchen().getAccount().getBalance());
}