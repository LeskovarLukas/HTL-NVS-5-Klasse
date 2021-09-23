//
// Created by Lukas Leskovar on 23.09.21.
//

#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "One argument expected!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::chrono::milliseconds sleeptime(500);

    while (true) {
        std::cout << argv[1] << std::endl;
        std::this_thread::sleep_for(sleeptime);
    }

    return 0;
}
