
#include <iostream>
#include <thread>

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
    while (true) {
        std::this_thread::sleep_for(1s);
        std::cout << ++lapCount << " Hyundai i130n" << std::endl;
    }
}