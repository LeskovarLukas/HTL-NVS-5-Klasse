#include <thread>
#include <iostream>

#include "../include/clock.h"
#include "../include/timeutils.h"

Clock::Clock(std::string name) {
    this->name = name;
    curr_time = std::chrono::system_clock::now();
}

Clock::Clock(std::string name_, int hours_, int minutes_, int seconds_) {
    this->name = name_;
    curr_time = std::chrono::system_clock::now();
    curr_time = ::set_time(curr_time, hours_, minutes_, seconds_);
}


void Clock::set_time(int hours_, int minutes_, int seconds_) {
    curr_time = ::set_time(curr_time, hours_, minutes_, seconds_);
}

std::tuple<int, int, int> Clock::get_time() {
    return ::get_time(curr_time);
}


long Clock::to_time() {
    return std::chrono::system_clock::to_time_t(curr_time);
}

void Clock::from_time(long time_) {
    curr_time = std::chrono::system_clock::from_time_t(time_);
}


void Clock::operator()() {
    std::ostringstream buffer;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        curr_time += std::chrono::duration<int, std::milli>(1000);

        buffer << name << ": " << curr_time << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}