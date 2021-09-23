//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

void startLoop(char, std::chrono::milliseconds);

int main() {
    pid_t pid{fork()};
    char charToPrint;
    std::chrono::milliseconds sleeptime(500);


    if (pid == 0) {
        charToPrint = 'A';
    } else {
        charToPrint = 'B';
    }
    startLoop(charToPrint, sleeptime);

    return 0;
}

void startLoop(char charToPrint, std::chrono::milliseconds sleeptime) {
    while (true) {
        std::cout << charToPrint << std::flush;
        std::this_thread::sleep_for(sleeptime);
    }
}