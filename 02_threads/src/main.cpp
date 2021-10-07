
#include <iostream>
#include <thread>
#include <random>
#include <sstream>
#include <iomanip>

#include "Car.h"

void hyundai_i10(int& totalTime);


int main() {
    int car1Time{};
    std::thread car1{hyundai_i10, std::ref(car1Time)};

    int car2Time;
    Car volvo = Car("Volvo V40");
    std::thread car2{volvo};

    car1.join();
    car2.join();
    car2Time = volvo.getTotalTime();

    std::cout << std::setprecision(3);
    if (car1Time < car2Time) {
        std::cout << "Sieger ist: Hyundai i10 mit " << car1Time / 1000.0 << "s\n";
        std::cout << "Verlierer ist:" << volvo.toString() << " mit " << car2Time / 1000.0 << "s\n";
    } else {
        std::cout << "Sieger ist:" << volvo.toString() << " mit " << car2Time / 1000.0 << "s\n";
        std::cout << "Verlierer ist: Hyundai i10 mit " << car1Time / 1000.0 << "s\n";
    }
    return 0;
}


void hyundai_i10(int& totalTime) {
    using namespace std::literals;

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::ostringstream buffer;
    int waitTime;
    totalTime = 0;

    buffer << std::setprecision(3);

    for (int lap = 0; lap < 10; lap++) {
        waitTime = dis(gen) * 1000;
        totalTime += waitTime;
        buffer << lap << " Hyundai i10: " << waitTime / 1000.0 << "s\n";

        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}