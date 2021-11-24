#include <iostream>
#include <mutex>
#include <thread>
#include "Philosopher.h"
#include "CLI11.hpp"

int main(int argc, char* argv[]) {
    CLI::App app("Dining philosophers simulation");

    bool noDeadlock = false;
    app.add_flag("-n,--nodeadlock", noDeadlock, "Prevent a deadlock at all");
    bool liveLock = false;
    app.add_flag("-l,--livelock", liveLock, "Simulate a livelock");
    CLI11_PARSE(app, argc, argv);


    Semaphore* leftForkSem = nullptr;
    if (noDeadlock) {
        leftForkSem = new Semaphore(4);
    }

    std::mutex forks[5];
    Philosopher philosophers[5] = {
        Philosopher(0, forks[0], forks[1], leftForkSem),
        Philosopher(1, forks[1], forks[2], leftForkSem),
        Philosopher(2, forks[2], forks[3], leftForkSem),
        Philosopher(3, forks[3], forks[4], leftForkSem),
        Philosopher(4, forks[4], forks[0], leftForkSem)
    };
    std::thread philosophersThreads[5];

    for (auto& philosopher : philosophers) {
        std::thread t{philosopher};  
        philosophersThreads[&philosopher - philosophers] = std::move(t);
    }

    for (auto& philosopher : philosophers) {
        philosophersThreads[&philosopher - philosophers].join();
    }

    delete leftForkSem;
    return 0;
}