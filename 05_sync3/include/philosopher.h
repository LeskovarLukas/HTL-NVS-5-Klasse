#pragma once 

#include <mutex>

class Philosopher
{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
public:
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork): id{id}, leftFork{leftFork}, rightFork{rightFork} {}

    void operator()();
    void printText(std::string);
};
