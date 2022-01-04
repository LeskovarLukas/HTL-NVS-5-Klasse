#include <iostream>
#include <thread>

#include "../include/clock.h"


class TimeSlave {
public: 
    TimeSlave(std::string name, int hour, int minute, int second): name(name), clock(Clock(name, hour, minute, second)) {
    };

    void operator()() {
        std::thread clock_thread(std::ref(this->clock));
        clock_thread.join();
    }
    
private:
    std::string name;
    Clock clock;
};


int main(){
    // 1)
    // std::thread clock{Clock("testclock")};
    // clock.join();

    // 2)
    // Clock clock("testclock", 12, 20, 0);
    // std::thread clock_thread(std::ref(clock));
    // clock_thread.join();

    // 3)
    // Clock clock("testclock");
    // clock.set_time(12, 20, 0);
    // std::thread clock_thread(std::ref(clock));
    // clock_thread.join();

    // 5)
    TimeSlave slave1("slave1", 12, 20, 0);
    TimeSlave slave2("slave2", 12, 30, 0);

    std::thread slave1_thread(std::ref(slave1));
    std::thread slave2_thread(std::ref(slave2));

    slave1_thread.join();
    slave2_thread.join();

    return 0;
}
