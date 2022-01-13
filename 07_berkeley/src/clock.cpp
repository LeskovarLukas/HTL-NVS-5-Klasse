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


void Clock::set_interval(long interval_) {
    interval = interval_;
}

void Clock::set_time_monotone(bool set_monotone) {
    if (set_monotone) {
        clock_monotone = 2000;
    } else {
        clock_monotone = 0;
    }
}


void Clock::operator()() {
    while (true)
    {
        std::unique_lock<std::mutex> print_lock(print_mutex);
        std::cout << name << ": " << curr_time << std::endl;
        print_lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(interval + clock_monotone));
        curr_time += std::chrono::duration<int, std::milli>(1000);
    }
}

std::mutex Clock::print_mutex;