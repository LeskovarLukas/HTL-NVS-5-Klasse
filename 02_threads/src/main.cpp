
#include <iostream>
#include <thread>
#include <random>
#include <sstream>
#include <iomanip>

#include "Car.h"

void hyundai_i10(int&, int);
int handleCommandLine(int , char*[]);
void help();
void error(std::string);


int main(int argc, char* argv[]) {
    int laps;

    if (argc == 1) {
        laps = 10;
    } else if (argc > 2) {
        error("Too many arguments: " + std::to_string(argc));
    } else {
        std::string argument = std::string(argv[1]);
        if (argument == "-h" || argument == "-help") {
            help();
        } else {
            try {
                size_t pos;
                laps = std::stoi(argument, &pos);

                if (pos != argument.size())
                    error("Could not convert: " + argument);

                if (laps < 1 || laps > 16)
                    error("Out of range (1 <= LAP'S < 16): " + argument);

            } catch (std::invalid_argument &) {
                error("Could not convert: " + argument);
            }
        }
    }

    int hyundaiTime{};
    std::thread hyundai_thread{hyundai_i10, std::ref(hyundaiTime), laps};

    int volvoTime;
    Car volvo = Car("Volvo V40", laps);
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


void hyundai_i10(int& totalTime, int laps) {
    using namespace std::literals;

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};
    std::ostringstream buffer;
    int waitTime;
    totalTime = 0;

    buffer << std::setprecision(3);

    for (int lap = 0; lap < laps; lap++) {
        waitTime = dis(gen) * 1000;
        totalTime += waitTime;
        buffer << lap << " Hyundai i10: " << waitTime / 1000.0 << "s\n";

        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}


void help() {
    std::cout << "Usage: contest [-h | --help | LAPS]" << std::endl;
    exit(EXIT_SUCCESS);
}


void error(std::string  msg="") {
    std::cerr << msg << std::endl << "Run with --help for more information." << std::endl;
    exit(EXIT_FAILURE);
}
