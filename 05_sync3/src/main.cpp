#include <iostream>
#include <mutex>
#include <thread>
#include "../include/Philosopher.h"

int main() {
    std::mutex forks[5];
    Philosopher philosophers[5] = {
        Philosopher(0, forks[0], forks[1]),
        Philosopher(1, forks[1], forks[2]),
        Philosopher(2, forks[2], forks[3]),
        Philosopher(3, forks[3], forks[4]),
        Philosopher(4, forks[4], forks[0])
    };
    std::thread philosophersThreads[5];

    for (auto& philosopher : philosophers) {
        std::thread t{philosopher};  
        philosophersThreads[&philosopher - philosophers] = std::move(t);
    }

    for (auto& philosopher : philosophers) {
        philosophersThreads[&philosopher - philosophers].join();
    }
    return 0;
}