#include "Account.h"

Account::Account(int starting_money) : balance(starting_money) {}

void Account::deposit(int amount) {
    balance += amount;
}

void Account::withdraw(int amount) {
    balance -= amount;
}

int Account::getBalance() const {
    return balance;
}