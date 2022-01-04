#include <thread>
#include <iostream>

#include "../include/clock.h"
#include "../include/timeutils.h"

Clock::Clock(std::string name) {
    this->name = name;
}

void Clock::operator()() {
    curr_time = std::chrono::system_clock::now();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        curr_time += std::chrono::duration<int, std::milli>(1000);

        std::cout << name << ": " << curr_time << std::endl;
    }
    
    
}