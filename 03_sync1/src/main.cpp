#include <iostream>
#include <thread>

#include "../include/account.h"

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

    //Punkt 2
//    account.deposit(1);
//
//    thread t1{[&]() {
//        std::cout << account.withdraw(1) << std::endl;
//    }};
//
//    thread t2{[&]() {
//        std::cout << account.withdraw(1) << std::endl;
//    }};

    Depositer depo1(account, 5);
    Depositer depo2(account, 5);

    std::thread t1{std::ref(depo1)};
    std::thread t2{std::ref(depo2)};

    t1.join();
    t2.join();

    std::cout << account.getBalance() << std::endl;

    return 0;
}
