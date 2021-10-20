//
// Created by Lukas Leskovar on 18.10.21.
//

#ifndef INC_03_SYNC1_ACCOUNT_H
#define INC_03_SYNC1_ACCOUNT_H

#include <mutex>

class Account {
private:
    int balance{};
    std::mutex balanceMutex{};

public:
    int getBalance();
    void deposit(int);
    bool withdraw(int);
};

class Depositer {
private:
    Account& account;

public:
    Depositer(Account& account) : account(account) {   }

    void operator()() {
        for (int i = 0; i < 5; i++) {
            account.deposit(1);
        }
    }
};

#endif //INC_03_SYNC1_ACCOUNT_H
