
#include <iostream>
#include <thread>
#include <random>

#include "Car.h"

void hyundai_i10();


int main() {
    std::thread car1{hyundai_i10};

    Car volvo = Car("Volvo V40");
    //std::thread car2{volvo};

    car1.join();
    return 0;
}


void hyundai_i10() {
    using namespace std::literals;

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::string output;
    int waitTime;

    int lapCount{};
    while (true) {
        output = std::to_string(++lapCount) + " Hyundai i10\n";
        waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << output << std::flush;
    }
}