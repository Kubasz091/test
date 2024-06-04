#include "gtest/gtest.h"
#include "Classes/Account.h"
#include "Classes/Bill.h"
#include "Classes/Customer.h"
#include "Classes/Menu.h"
#include "Classes/Dish.h"
#include "Classes/Recipe.h"
#include "Classes/Ingredient.h"
#include "Classes/Kitchen.h"
#include "Classes/Shop.h"
#include "Classes/Menu.h"
#include "Classes/Table.h"
#include "Classes/Waiter.h"

TEST(AccountTest, Deposit) {
    Account account(100.0);
    account.deposit(50.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 150.0);

    account.deposit(0.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 150.0);
}

TEST(AccountTest, Withdraw) {
    Account account(100.0);
    account.withdraw(50.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 50.0);

    account.withdraw(0.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 50.0);
}

TEST(AccountTest, GetBalance) {
    Account account(100.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 100.0);

    account.deposit(50.0);
    EXPECT_DOUBLE_EQ(account.getBalance(), 150.0);
}

TEST(BillTest, AddOrder) {
    Bill bill;
    bill.addOrder("Coffee", 2.5);
    EXPECT_DOUBLE_EQ(bill.pay(), 2.5);

    bill.addOrder("", 0.0);
    EXPECT_DOUBLE_EQ(bill.pay(), 2.5);
}

TEST(BillTest, Pay) {
    Bill bill;
    bill.addOrder("Coffee", 2.5);
    EXPECT_DOUBLE_EQ(bill.pay(), 2.5);

    bill.addOrder("Tea", 2.0);
    EXPECT_DOUBLE_EQ(bill.pay(), 4.5);
}

TEST(BillTest, IsPaid) {
    Bill bill;
    EXPECT_FALSE(bill.isPaid());

    bill.pay();
    EXPECT_TRUE(bill.isPaid());
}

TEST(CustomerTest, Order) {
    Menu menu;
    menu.addDish(MenuPosition{"Coffee", 2.5});
    menu.addDish(MenuPosition{"Tea", 2.0});

    Customer customer(1);
    MenuPosition ordered = customer.order(menu);
    EXPECT_DOUBLE_EQ(customer.pay(), ordered.price);
}

TEST(CustomerTest, GetId) {
    Customer customer(1);
    EXPECT_EQ(customer.getId(), 1);
}

TEST(CustomerTest, Timer) {
    Customer customer(1);
    customer.setTimer(0.0);
    EXPECT_TRUE(customer.checkIfReady());

    customer.setTimer(10.0);
    EXPECT_FALSE(customer.checkIfReady());
}

TEST(CustomerTest, Pay) {
    Menu menu;
    menu.addDish(MenuPosition{"Coffee", 2.5});

    Customer customer(1);
    customer.order(menu);
    EXPECT_DOUBLE_EQ(customer.pay(), 2.5);
}

TEST(CustomerTest, OperatorEquals) {
    Customer customer1(1);
    Customer customer2(1);
    EXPECT_TRUE(customer1 == customer2);

    Customer customer3(2);
    EXPECT_FALSE(customer1 == customer3);
}

TEST(DishTest, Timer) {
    Dish dish;
    dish.setTimer(0.0);
    EXPECT_TRUE(dish.checkIfReady());

    dish.setTimer(10.0);
    EXPECT_FALSE(dish.checkIfReady());
}

TEST(DishTest, GetRecipe) {
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    Dish dish(recipe, 1);
    EXPECT_EQ(dish.getRecipe().getName(), "Coffee");
}

TEST(DishTest, GetCustomer) {
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    Dish dish(recipe, 1);
    EXPECT_EQ(dish.getCustomer(), 1);
}

TEST(DishTest, OperatorEquals) {
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    Dish dish1(recipe, 1);
    Dish dish2 = dish1;
    EXPECT_EQ(dish2.getRecipe().getName(), "Coffee");
    EXPECT_EQ(dish2.getCustomer(), 1);
}

TEST(DishTest, Empty) {
    Dish dish;
    EXPECT_TRUE(dish.empty());

    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    Dish dish2(recipe, 1);
    EXPECT_FALSE(dish2.empty());
}

TEST(IngredientTest, GetName) {
    Ingredient ingredient("Coffee", 2.5);
    EXPECT_EQ(ingredient.getName(), "Coffee");
}

TEST(IngredientTest, GetCost) {
    Ingredient ingredient("Coffee", 2.5);
    EXPECT_DOUBLE_EQ(ingredient.getCost(), 2.5);
}

TEST(IngredientTest, OperatorEquals) {
    Ingredient ingredient1("Coffee", 2.5);
    Ingredient ingredient2 = ingredient1;
    EXPECT_EQ(ingredient2.getName(), "Coffee");
    EXPECT_DOUBLE_EQ(ingredient2.getCost(), 2.5);
}

TEST(KitchenTest, PrepareDish) {
    Kitchen kitchen(2, 100.0);
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    double normalCookingTime = 5.0;
    double expectedTime = kitchen.prepareDish(recipe, normalCookingTime);
    EXPECT_DOUBLE_EQ(expectedTime, 4.0);
}

TEST(KitchenTest, GetShop) {
    Kitchen kitchen(2, 100.0);
    Shop& shop = kitchen.getShop();
    EXPECT_EQ(&shop, &kitchen.getShop());
}

TEST(KitchenTest, GetAccount) {
    Kitchen kitchen(2, 100.0);
    Account& account = kitchen.getAccount();
    EXPECT_EQ(&account, &kitchen.getAccount());
}

TEST(MenuTest, AddRecipe) {
    Menu menu;
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    menu.addRecipe(recipe, 2.5);
    EXPECT_EQ(menu.getRecipe("Coffee").getName(), "Coffee");
}

TEST(MenuTest, GetPrice) {
    Menu menu;
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    menu.addRecipe(recipe, 2.5);
    EXPECT_DOUBLE_EQ(menu.getPrice("Coffee"), 2.5);
}

TEST(MenuTest, GetRecipe) {
    Menu menu;
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    menu.addRecipe(recipe, 2.5);
    EXPECT_EQ(menu.getRecipe("Coffee").getName(), "Coffee");
}

TEST(MenuTest, GetDishes) {
    Menu menu;
    Recipe recipe("Coffee", {{"Water", 1}, {"Coffee", 1}});
    menu.addRecipe(recipe, 2.5);
    auto dishes = menu.getDishes();
    EXPECT_EQ(dishes.size(), 1);
    EXPECT_EQ(dishes[0].recipe.getName(), "Coffee");
    EXPECT_DOUBLE_EQ(dishes[0].price, 2.5);
}

TEST(RecipeTest, CalculateCost) {
    Ingredient ingredient1("Coffee", 2.5);
    Ingredient ingredient2("Water", 1.0);
    IngredientQuantity iq1(ingredient1, 2);
    IngredientQuantity iq2(ingredient2, 1);
    Recipe recipe("Coffee", {iq1, iq2});
    EXPECT_DOUBLE_EQ(recipe.calculateCost(), 6.0);
}

TEST(RecipeTest, GetName) {
    Ingredient ingredient1("Coffee", 2.5);
    IngredientQuantity iq1(ingredient1, 2);
    Recipe recipe("Coffee", {iq1});
    EXPECT_EQ(recipe.getName(), "Coffee");
}

TEST(RecipeTest, GetIngredients) {
    Ingredient ingredient1("Coffee", 2.5);
    IngredientQuantity iq1(ingredient1, 2);
    Recipe recipe("Coffee", {iq1});
    auto ingredients = recipe.getIngredients();
    EXPECT_EQ(ingredients.size(), 1);
    EXPECT_EQ(ingredients[0].ingredient.getName(), "Coffee");
    EXPECT_EQ(ingredients[0].quantity, 2);
}

TEST(RecipeTest, OperatorEquals) {
    Ingredient ingredient1("Coffee", 2.5);
    IngredientQuantity iq1(ingredient1, 2);
    Recipe recipe1("Coffee", {iq1});
    Recipe recipe2 = recipe1;
    EXPECT_EQ(recipe2.getName(), "Coffee");
    auto ingredients = recipe2.getIngredients();
    EXPECT_EQ(ingredients.size(), 1);
    EXPECT_EQ(ingredients[0].ingredient.getName(), "Coffee");
    EXPECT_EQ(ingredients[0].quantity, 2);
}

TEST(ShopTest, ConstructorTest) {
    Shop shop;
    ASSERT_EQ(shop.getTotalSpent(), 0);
}

TEST(ShopTest, AddIngredientTest) {
    Shop shop;
    shop.addIngredient("Cheese", 1.0);
    ASSERT_EQ(shop.getIngredientPrice("Cheese"), 1.0);
}

TEST(ShopTest, BuyIngredientTest) {
    Shop shop;
    shop.addIngredient("Cheese", 1.0);
    ASSERT_EQ(shop.buyIngredient("Cheese", 100), 1.0);
    ASSERT_EQ(shop.getTotalSpent(), 1.0);
}

TEST(ShopTest, GetIngredientTest) {
    Shop shop;
    shop.addIngredient("Cheese", 1.0);
    Ingredient cheese = shop.getIngredient("Cheese");
    ASSERT_EQ(cheese.getName(), "Cheese");
    ASSERT_EQ(cheese.getCost(), 1.0);
}

TEST(ShopTest, GetIngredientPriceTest) {
    Shop shop;
    shop.addIngredient("Cheese", 1.0);
    ASSERT_EQ(shop.getIngredientPrice("Cheese"), 1.0);
}

TEST(ShopTest, GetTotalSpentTest) {
    Shop shop;
    shop.addIngredient("Cheese", 1.0);
    shop.buyIngredient("Cheese", 100);
    ASSERT_EQ(shop.getTotalSpent(), 1.0);
}

TEST(TableTest, SeatCustomerTest) {
    Table table;
    Customer customer(1, "John Doe");
    table.seatCustomer(customer);
    ASSERT_EQ(table.getCustomer().getId(), 1);
    ASSERT_EQ(table.getCustomer().getName(), "John Doe");
    ASSERT_TRUE(table.isOccupied());
}

TEST(TableTest, IsOccupiedTest) {
    Table table;
    ASSERT_FALSE(table.isOccupied());
    Customer customer(1, "John Doe");
    table.seatCustomer(customer);
    ASSERT_TRUE(table.isOccupied());
}

TEST(TableTest, RemoveCustomerTest) {
    Table table;
    Customer customer(1, "John Doe");
    table.seatCustomer(customer);
    table.removeCustomer();
    ASSERT_FALSE(table.isOccupied());
}

TEST(TableTest, GetCustomerTest) {
    Table table;
    Customer customer(1, "John Doe");
    table.seatCustomer(customer);
    Customer seatedCustomer = table.getCustomer();
    ASSERT_EQ(seatedCustomer.getId(), 1);
    ASSERT_EQ(seatedCustomer.getName(), "John Doe");
}

TEST(WaiterTest, TakeOrderFromCustomerTest) {
    Waiter waiter;
    waiter.takeOrderFromCustomer(1);
    ASSERT_EQ(waiter.getCurrentCustomer(), 1);
}

TEST(WaiterTest, TakeDishTest) {
    Waiter waiter;
    Dish dish("Pizza", std::vector<Ingredient>{Ingredient("Cheese", 1.0)});
    waiter.takeDish(dish);
    ASSERT_EQ(waiter.getCurrentDish().getName(), "Pizza");
}

TEST(WaiterTest, SetTimerTest) {
    Waiter waiter;
    waiter.setTimer(1.0);
    ASSERT_FALSE(waiter.checkIfReady());
    std::this_thread::sleep_for(std::chrono::seconds(2));
    ASSERT_TRUE(waiter.checkIfReady());
}

TEST(WaiterTest, SetCustomerPayingTest) {
    Waiter waiter;
    waiter.setCustomerPaying(true);
    ASSERT_TRUE(waiter.getCustomerPaying());
}

TEST(WaiterTest, HaveDishTest) {
    Waiter waiter;
    ASSERT_FALSE(waiter.haveDish());
    Dish dish("Pizza", std::vector<Ingredient>{Ingredient("Cheese", 1.0)});
    waiter.takeDish(dish);
    ASSERT_TRUE(waiter.haveDish());
}

TEST(WaiterTest, HaveCustomerTest) {
    Waiter waiter;
    ASSERT_FALSE(waiter.haveCustomer());
    waiter.takeOrderFromCustomer(1);
    ASSERT_TRUE(waiter.haveCustomer());
}
