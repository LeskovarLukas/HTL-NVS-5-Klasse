#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include "../include/Philosopher.h"


void Philosopher::operator()()
{
    while (true) {
        println({"Philosopher", std::to_string(id), "is thinking..."});
        std::this_thread::sleep_for(std::chrono::seconds(1));

        println({"Philosopher", std::to_string(id), "attempts to get left fork"});
        leftFork.lock();

        println({"Philosopher", std::to_string(id), "got left fork. Now he wants the right one..."});
        rightFork.lock();

        println({"Philosopher", std::to_string(id), "got right fork. Now he is eating..."});
        std::this_thread::sleep_for(std::chrono::seconds(2));
        println({"Philosopher", std::to_string(id), "finished eating"});

        leftFork.unlock();
        println({"Philosopker", std::to_string(id), "released left fork"});
        
        rightFork.unlock();
        println({ "Philosopher", std::to_string(id), "released right fork"});
    }
}

void Philosopher::println(const std::vector<std::string>& text) {
    std::lock_guard<std::mutex> lock(Philosopher::out_mtx);

    for (auto& line : text) {
        std::cout << line << " ";
    }
    std::cout << std::endl;
}


std::mutex Philosopher::out_mtx;