#include <iostream>
#include <thread>

#include "../include/account.h"

using namespace std;

int main() {
    Account account;

    //Punkt 1
//    account.deposit(15);
//    std::cout << account.getBalance() << std::endl;
//
//    account.withdraw(6);
//    std::cout << account.getBalance() << std::endl;
//
//    std::cout << account.withdraw(10) << std::endl;
//    std::cout << account.getBalance() << std::endl;

    account.deposit(1);

    thread t1{[&]() {
        std::cout << account.withdraw(1) << std::endl;
    }};

    thread t2{[&]() {
        std::cout << account.withdraw(1) << std::endl;
    }};

    t1.join();
    t2.join();

    return 0;
}
