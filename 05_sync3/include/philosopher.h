#pragma once 

#include <vector>
#include <mutex>

class Philosopher
{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
    static std::mutex out_mtx;
public:
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork): id{id}, leftFork{leftFork}, rightFork{rightFork} {
    }

    void operator()();
    void println(const std::initializer_list<std::string>&);
};
