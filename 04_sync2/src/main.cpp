#include "../include/work_queue.h"
#include <iostream>
#include <thread>

int main() {
    WorkQueue queue = WorkQueue();
    int counter = 0;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        queue.push(WorkPacket(counter++));       

        std::cout << "B: Submitted work packet " << counter << std::endl;
    }
    

    return 0;
}