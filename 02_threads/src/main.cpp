
#include <iostream>
#include <thread>
#include <random>
#include <sstream>
#include <iomanip>

#include "Car.h"

void hyundai_i10(int& totalTime);


int main() {
    int hyundaiTime{};
    std::thread hyundai_thread{hyundai_i10, std::ref(hyundaiTime)};

    int volvoTime;
    Car volvo = Car("Volvo V40");
    std::thread volvoThread{std::ref(volvo)};

    hyundai_thread.join();
    volvoThread.join();
    volvoTime = volvo.getTotalTime();

    std::cout << std::setprecision(3);
    if (hyundaiTime < volvoTime) {
        std::cout << "Sieger ist: Hyundai i10 mit " << hyundaiTime / 1000.0 << "s\n";
        std::cout << "Verlierer ist:" << volvo.toString() << " mit " << volvoTime / 1000.0 << "s\n";
    } else {
        std::cout << "Sieger ist:" << volvo.toString() << " mit " << volvoTime / 1000.0 << "s\n";
        std::cout << "Verlierer ist: Hyundai i10 mit " << hyundaiTime / 1000.0 << "s\n";
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