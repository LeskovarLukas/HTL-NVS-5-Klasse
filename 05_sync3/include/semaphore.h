#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    int value;
    std::mutex sem_mtx;
    std::condition_variable sem_cv;

public:
    Semaphore(int init): value{init} {}
    Semaphore() : Semaphore{0} {};
    void aquire();
    void release();
    int available_permits();
};