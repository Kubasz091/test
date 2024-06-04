#include "Bill.h"

Bill::Bill() : totalCost(0), paid(false) {}

void Bill::addOrder(const std::string& orderName, int price) {
    orders.push_back(orderName);
    totalCost += price;
}

int Bill::pay() {
    paid = true;
    return totalCost;
}

bool Bill::isPaid() const {
    return paid;
}