
#include <iostream>
#include <thread>
#include <random>
#include <sstream>
#include <iomanip>

#include "Car.h"

void hyundai_i10();


int main() {
    std::thread car1{hyundai_i10};

    Car volvo = Car("Volvo V40");
    std::thread car2{volvo};

    car1.join();
    return 0;
}


void hyundai_i10() {
    using namespace std::literals;

    int lapCount{};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::ostringstream buffer;
    int waitTime;


    while (true) {
        waitTime = dis(gen) * 1000;
        buffer << std::setprecision(3) << lapCount++ << " Hyundai i10: " << waitTime / 1000.0 << "s\n";

        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}