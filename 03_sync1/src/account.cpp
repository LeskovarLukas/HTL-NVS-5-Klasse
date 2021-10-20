//
// Created by Lukas Leskovar on 18.10.21.
//

#include <thread>

#include "../include/account.h"

int Account::getBalance() {
    return balance;
}

void Account::deposit(int amount) {
    std::unique_lock<std::mutex> lock(balanceMutex);
    balance += amount;
    lock.unlock();
}

bool Account::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(balanceMutex);
    if (balance - amount >= 0) {
        std::this_thread::yield();
        balance -= amount;
        return true;
    }
    return false;
}