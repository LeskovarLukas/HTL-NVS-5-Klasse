#pragma once 

#include <vector>
#include <mutex>
#include <thread>
#include "semaphore.h"

class Philosopher
{
private:
    int id;
    std::timed_mutex& leftFork;
    std::timed_mutex& rightFork;
//  static std::mutex out_mtx;
    Semaphore* leftForkSem;
    static std::mutex leftForkSem_mtx;
public:
    Philosopher(int id, std::timed_mutex& leftFork, std::timed_mutex& rightFork, Semaphore* sem):
        id{id}, leftFork{leftFork}, rightFork{rightFork}, leftForkSem{sem} {
    }

    void operator()(bool);
//  void println(const std::initializer_list<std::string>&);
};
