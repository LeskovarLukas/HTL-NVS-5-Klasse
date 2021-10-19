#include <iostream>
#include <thread>

#include "../include/account.h"

using namespace std;

int main() {
    Account account;

    account.deposit(15);
    std::cout << account.getBalance() << std::endl;

    account.withdraw(6);
    std::cout << account.getBalance() << std::endl;

    std::cout << account.withdraw(10) << std::endl;
    std::cout << account.getBalance() << std::endl;

    return 0;
}
