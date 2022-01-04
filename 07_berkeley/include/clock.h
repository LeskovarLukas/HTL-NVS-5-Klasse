#pragma once

#include <string>
#include <chrono>

class Clock {
public:
    Clock(std::string);
    Clock(std::string, int, int, int);

    void set_time(int, int, int);
    std::tuple<int, int, int> get_time();

    void operator()();

private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;
};