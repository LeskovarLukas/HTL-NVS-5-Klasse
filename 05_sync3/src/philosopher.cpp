#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include "../include/Philosopher.h"


void Philosopher::operator()()
{
    while (true) {
        printText("is thinking...");
        std::this_thread::sleep_for(std::chrono::seconds(1));

        printText("attempts to get left fork");
        leftFork.lock();

        printText("got left fork. Now he wants the right one...");
        rightFork.lock();

        printText("got right fork. Now he is eating...");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        printText("finished eating");

        leftFork.unlock();
        printText("released left fork");
        
        rightFork.unlock();
        printText("released right fork");
    }
}

void Philosopher::printText(std::string text) {
    std::ostringstream oss;
    oss << "Philosopher " << id << " " << text;
    std::cout << oss.str() << std::endl;
}