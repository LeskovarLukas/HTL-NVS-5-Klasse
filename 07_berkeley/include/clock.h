#pragma once

#include <string>
#include <chrono>

class Clock {
public:
    Clock(std::string);
    Clock(std::string, int, int, int);

    void set_time(int, int, int);
    std::tuple<int, int, int> get_time();

    long to_time();
    void from_time(long);

    void operator()();

private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;
};