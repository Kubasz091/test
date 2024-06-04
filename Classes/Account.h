#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    int balance;
public:
    Account(int startin_money);
    void deposit(int amount);
    void withdraw(int amount);
    int getBalance() const;
};

#endif