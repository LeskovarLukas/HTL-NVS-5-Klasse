#include <iostream>
#include <thread>

#include "../include/clock.h"

int main(){
    // 1)
    // std::thread clock{Clock("testclock")};
    // clock.join();

    // 2)
    Clock clock("testclock", 4, 20, 0);
    std::thread clock_thread(std::ref(clock));
    clock_thread.join();

    return 0;
}
