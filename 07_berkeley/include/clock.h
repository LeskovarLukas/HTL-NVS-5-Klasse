#pragma once

#include <string>
#include <chrono>

class Clock {
public:
    Clock(std::string);
    Clock(std::string, int, int, int);

    void operator()();

private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;
};