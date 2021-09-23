//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>

void startLoop(char);

int main() {
    pid_t pid{fork()};
    char charToPrint;


    if (pid == 0) {
        charToPrint = 'A';
    } else {
        charToPrint = 'B';
    }
    startLoop(charToPrint);

    return 0;
}

void startLoop(char charToPrint) {
    while (true) {
        std::cout << charToPrint << std::flush;
        usleep(500000);
    }
}