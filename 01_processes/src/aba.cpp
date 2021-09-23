//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <csignal>

void startChildLoop(char, std::chrono::milliseconds);

int main() {
    pid_t pid{fork()};
    std::chrono::milliseconds sleeptime(500);


    if (pid == 0) {
        if (execl("./charout", "charout", "A", nullptr)) {
            std::cerr << "\nstarting charout failed: No such file or directory" << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cout << "Child PID: " << pid << std::endl;

        for (int i = 0; i < 6; i++) {
            std::cout << "B" << std::flush;
            std::this_thread::sleep_for(sleeptime);
        }
        kill(pid, SIGKILL);
        int status;
        waitpid(pid, &status, 0);
        std::cout << "\nChild finished with exit code: " << WIFEXITED(status) << std::endl;
    }

    exit(EXIT_SUCCESS);
}

void startChildLoop(char charToPrint, std::chrono::milliseconds sleeptime) {
    while (true) {
        std::cout << charToPrint << std::flush;
        std::this_thread::sleep_for(sleeptime);
    }
}