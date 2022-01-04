#include <iostream>
#include <thread>

#include "../include/clock.h"

int main(){
    std::thread clock{Clock("testclock")};
    clock.join();

    return 0;
}
