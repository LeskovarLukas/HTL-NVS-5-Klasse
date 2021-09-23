//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>

int main() {
    pid_t pid{fork()};

    if (pid == 0) {
        do {
            std::cout << "B" << std::flush;
            usleep(500000);
        } while (true);
    } else {
        do {
            std::cout << "A" << std::flush;
            usleep(500000);
        } while (true);
    }

    return 0;
}
