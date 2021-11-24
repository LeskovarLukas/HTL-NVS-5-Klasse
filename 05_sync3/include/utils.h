#pragma once

#include <iostream>
#include <mutex>

extern std::recursive_mutex out_mtx;

void println();

template<typename T, typename... Rest>
void println(const T& t, const Rest&... rest) {
    std::lock_guard<std::recursive_mutex> lock(out_mtx);
    std::cout << t << " ";
    println(rest...);
}