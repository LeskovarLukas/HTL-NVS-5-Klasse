//
// Created by Lukas Leskovar on 06.10.21.
//

#include <iostream>
#include <thread>
#include "include/Car.h"

void Car::driveLaps() {
    using namespace std::literals;
    int lapCount{};
    while (true) {
        std::this_thread::sleep_for(1s);
        std::cout << ++lapCount << " " << this->carType << std::endl;
    }
}

Car::Car(std::string carType) {
    this->carType = carType;
}

void Car::operator()() {
    driveLaps();
}