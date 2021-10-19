//
// Created by Lukas Leskovar on 18.10.21.
//

#include <thread>

#include "../include/account.h"

int Account::getBalance() {
    return balance;
}

void Account::deposit(int amount) {
    balance += amount;
}

bool Account::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(withdrawMutex);
    if (balance - amount >= 0) {
        std::this_thread::yield();
        balance -= amount;
        return true;
    }
    return false;
}