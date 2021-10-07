//
// Created by Lukas Leskovar on 06.10.21.
//

#include <iostream>
#include <thread>
#include <utility>
#include <random>
#include <iomanip>
#include <sstream>

#include "include/Car.h"

void Car::driveLaps() {
    using namespace std::literals;

    int lapCount{};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::ostringstream buffer;
    int waitTime;


    while (true) {
        waitTime = dis(gen) * 1000;
        buffer << std::setprecision(3) << lapCount++ << " " << this->carType << ": " << waitTime / 1000.0 << "s\n";

        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}

Car::Car(std::string carType) {
    this->carType = std::move(carType);
}

void Car::operator()() {
    driveLaps();
}