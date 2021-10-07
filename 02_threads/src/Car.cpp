//
// Created by Lukas Leskovar on 06.10.21.
//

#include <iostream>
#include <thread>
#include <utility>
#include "include/Car.h"

void Car::driveLaps() {
    using namespace std::literals;
    int lapCount{};
    while (true) {
        std::string output = std::to_string(++lapCount) + " " + this->carType + "\n";
        std::this_thread::sleep_for(1s);
        std::cout << output <<std::flush;
    }
}

Car::Car(std::string carType) {
    this->carType = std::move(carType);
}

void Car::operator()() {
    driveLaps();
}