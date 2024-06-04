#ifndef BILL_H
#define BILL_H

#include <vector>
#include <string>
#include "Recipe.h"
#include "Menu.h"

class Bill {
private:
    std::vector<std::string> orders;
    int totalCost = 0;
    bool paid;
public:
    Bill();
    void addOrder(const std::string& orderName, int price);
    int pay();
    bool isPaid() const;
};

#endif