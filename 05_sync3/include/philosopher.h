#pragma once 

#include <vector>
#include <mutex>
#include "semaphore.h"

class Philosopher
{
private:
    int id;
    std::mutex& leftFork;
    std::mutex& rightFork;
//  static std::mutex out_mtx;
    Semaphore* leftForkSem;
    static std::mutex leftForkSem_mtx;
public:
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork, Semaphore* sem): 
        id{id}, leftFork{leftFork}, rightFork{rightFork}, leftForkSem{sem} {
    }

    void operator()();
//  void println(const std::initializer_list<std::string>&);
};
