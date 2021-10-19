//
// Created by Lukas Leskovar on 18.10.21.
//

#include "../include/account.h"

int Account::getBalance() {
    return balance;
}

void Account::deposit(int amount) {
    balance += amount;
}

bool Account::withdraw(int amount) {
    if (balance - amount >= 0) {
        balance -= amount;
        return true;
    }
    return false;
}