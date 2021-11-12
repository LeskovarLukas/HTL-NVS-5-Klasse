#include "../include/work_queue.h"
#include <iostream>
#include <thread>

void worker(int, WorkQueue&);


int main() {
    WorkQueue queue = WorkQueue();
    int counter = 0;

    std::thread t1(worker, 1, std::ref(queue));
    std::thread t2(worker, 2, std::ref(queue));

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        queue.push(WorkPacket(counter++));       

        std::cout << "B: Submitted work packet " << counter << std::endl;
    }
    

    return 0;
}


void worker(int id, WorkQueue& q) {
    while(true) {
        std::cout << "W" << id << ": want work packet" << std::endl;
        WorkPacket p = q.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "W" << id << ": Processed work packet " << p.getID() << std::endl;
    }
}