#include <iostream>

#include "semaphore.h"

void Semaphore::aquire() {
    std::unique_lock<std::mutex> lck(sem_mtx);
    sem_cv.wait(lck, [this] { return value > 0; });
    --value;
}

void Semaphore::release() {
    std::lock_guard<std::mutex> lck(sem_mtx);
    ++value;
    sem_cv.notify_one();
}

int Semaphore::available_permits() {
    std::lock_guard<std::mutex> lck(sem_mtx);
    return value;
}