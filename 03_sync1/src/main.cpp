#include <iostream>
#include <thread>

#include "../include/account.h"
#include "../include/CLI11.hpp"

int main(int argc, char* argv[]) {
    CLI::App app("Account app");

    int balance{0};
    app.add_option("balance", balance, "Initial balance")->required();
    int deposits{5};
    app.add_option("-d,--deposits", deposits, "Count of deposits")->default_val(deposits);
    CLI11_PARSE(app, argc, argv);

    Account account(balance);

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

    Depositer depo1(account, deposits);
    Depositer depo2(account, deposits);

    std::thread t1{std::ref(depo1)};
    std::thread t2{std::ref(depo2)};

    t1.join();
    t2.join();

    std::cout << account.getBalance() << std::endl;

    return 0;
}
