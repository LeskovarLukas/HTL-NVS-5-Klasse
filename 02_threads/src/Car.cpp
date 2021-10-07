//
// Created by Lukas Leskovar on 06.10.21.
//

#include <iostream>
#include <thread>
#include <utility>
#include <random>

#include "include/Car.h"

void Car::driveLaps() {
    using namespace std::literals;

    int lapCount{};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::string output;
    int waitTime;

    while (true) {
        std::string output = std::to_string(++lapCount) + " " + this->carType + "\n";
        waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << output << std::flush;
    }
}

Car::Car(std::string carType) {
    this->carType = std::move(carType);
}

void Car::operator()() {
    driveLaps();
}