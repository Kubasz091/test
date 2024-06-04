cmake_minimum_required(VERSION 3.14)
project(Projekt1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(spdlog REQUIRED)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_MakeAvailable(json)
add_executable(main
    main.cpp
    Simulation.cpp
    Classes/Account.cpp
    Classes/Bill.cpp
    Classes/Customer.cpp
    Classes/Dish.cpp
    Classes/Ingredient.cpp
    Classes/Kitchen.cpp
    Classes/Menu.cpp
    Classes/Recipe.cpp
    Classes/Restaurant.cpp
    Classes/Shop.cpp
    Classes/Table.cpp
    Classes/Waiter.cpp
    Classes/Account.h
    Classes/Bill.h
    Classes/Customer.h
    Classes/Dish.h
    Classes/Ingredient.h
    Classes/Kitchen.h
    Classes/Menu.h
    Classes/Recipe.h
    Classes/Restaurant.h
    Classes/Shop.h
    Classes/Table.h
    Classes/Waiter.h)
add_executable(
        tests
        tests.cpp
        Classes/Account.cpp
        Classes/Bill.cpp
        Classes/Customer.cpp
        Classes/Dish.cpp
        Classes/Ingredient.cpp
        Classes/Kitchen.cpp
        Classes/Menu.cpp
        Classes/Recipe.cpp
        Classes/Shop.cpp
        Classes/Table.cpp
        Classes/Waiter.cpp
      )

target_link_libraries(main PRIVATE spdlog::spdlog)
target_link_libraries(main PRIVATE ncurses)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

