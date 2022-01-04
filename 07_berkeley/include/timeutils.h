#ifndef TIME_UTILS_H
#define TIME_UTILS_H

// Günter Kolousek, 2016

#include <chrono>
#include <ctime>
#include <iomanip>


inline std::ostream& operator<<(std::ostream& out, decltype(std::chrono::system_clock::now()) time) {
    std::time_t t{std::chrono::system_clock::to_time_t(time)};
    out << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return out;
}


inline auto get_time(decltype(std::chrono::system_clock::now()) time) {
    std::time_t t{std::chrono::system_clock::to_time_t(time)};
    std::tm* ptm{std::localtime(&t)};
    return std::make_tuple(ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
}


inline auto set_time(decltype(std::chrono::system_clock::now())& time, int hours, int minutes, int seconds) {
    std::time_t t{std::chrono::system_clock::to_time_t(time)};
    std::tm* ptm{std::localtime(&t)};
    ptm->tm_hour = hours;
    ptm->tm_min = minutes;
    ptm->tm_sec = seconds;
    t = std::mktime(ptm);
    return std::chrono::system_clock::from_time_t(t);
}
#endif
