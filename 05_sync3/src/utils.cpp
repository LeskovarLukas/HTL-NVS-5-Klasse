#include "utils.h"

std::recursive_mutex out_mtx;

void println() {
    std::lock_guard<std::recursive_mutex> lock(out_mtx);
    std::cout << std::endl;
}

