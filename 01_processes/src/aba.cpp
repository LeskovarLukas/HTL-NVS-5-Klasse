//
// Created by Lukas Leskovar on 20.09.21.
//

#include <iostream>
#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <wait.h>

void startCharout(const char*);

void killSubprocess(pid_t);

int main() {
    pid_t pidA{fork()};

    if (pidA == 0) {
        startCharout(getenv("ABA_LETTER_A"));
    } else {
        pid_t pidB{fork()};

        if (pidB == 0) {
            startCharout(getenv("ABA_LETTER_B"));
        } else {
            std::cout << "waiting for 3 seconds" << std::endl;
            sleep(3);
            std::cout << "\nkilling both subprocesses with pids " << pidA << " and " << pidB << "\n";
            std::cout << "waiting for both subprocesses to be dead";
            killSubprocess(pidA);
            killSubprocess(pidB);
        }
    }

    exit(EXIT_SUCCESS);
}

void startCharout(const char* strToPrint) {
    if (strToPrint == nullptr) {
        std::cerr << "starting charout failed: Nothing to print" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (execl("./charout", "charout", strToPrint, nullptr)) {
        std::cerr << "starting charout failed: No such file or directory" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void killSubprocess(pid_t pid) {
    kill(pid, SIGKILL);
    int status;
    waitpid(pid, &status, 0);
    std::cout << "\nsubprocess " << pid << " exited with " << WIFEXITED(status) << std::flush;
}