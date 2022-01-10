#pragma once

#include <string>
#include <chrono>
#include <mutex>

class Clock {
public:
    Clock(std::string);
    Clock(std::string, int, int, int);

    void set_time(int, int, int);
    std::tuple<int, int, int> get_time();

    long to_time();
    void from_time(long);

    void set_interval(long);
    void set_time_monotone(bool);

    void operator()();

private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;
    long interval{1000}; // in milliseconds
    long clock_monotone{0};
    static std::mutex print_mutex;
};