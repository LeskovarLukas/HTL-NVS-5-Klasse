//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>
#include <csignal>
#include <cstdlib>

void startCharout(char);

void killSubprocess(pid_t);

int main() {
    pid_t pidA{fork()};


    if (pidA == 0) {
        startCharout(*getenv("ABA_LETTER_A"));
    } else {
        pid_t pidB{fork()};

        if (pidB == 0) {
            startCharout(*getenv("ABA_LETTER_B"));
        } else {
            std::cout << "waiting for 3 seconds" << std::endl;
            sleep(3);
            killSubprocess(pidA);
            killSubprocess(pidB);
        }
    }

    exit(EXIT_SUCCESS);
}

void startCharout(char charToPrint) {
    char param[2];
    sprintf(param, "%c", charToPrint);

    if (execl("./charout", "charout", param, nullptr)) {
        std::cerr << "\nstarting charout failed: No such file or directory" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void killSubprocess(pid_t pid) {
    kill(pid, SIGKILL);
    int status;
    waitpid(pid, &status, 0);
    std::cout << "\nChild finished with exit code: " << WIFEXITED(status) << std::flush;
}