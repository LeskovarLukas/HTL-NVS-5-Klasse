#include <iostream>
#include <thread>
#include <sstream>
#include "../include/work_queue.h"

void worker(int, WorkQueue&);


int main() {
    WorkQueue queue{};
    int counter = 0;
    std::ostringstream buffer;

    std::thread t1(worker, 1, std::ref(queue));
    std::thread t2(worker, 2, std::ref(queue));

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::lock_guard<std::mutex> lock(queue.queue_mutex);
        queue.push(WorkPacket(counter)); 

        buffer << "B: Submitted work packet " << counter++ << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        queue.not_empty.notify_one();
    }
    
    t1.join();
    t2.join();

    return 0;
}


void worker(int id, WorkQueue& q) {
    std::ostringstream buffer;

    while(true) {
        buffer << "W" << id << ": Want work packet" << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        std::unique_lock<std::mutex> lock(q.queue_mutex);
        q.not_empty.wait(lock);

        WorkPacket p = q.pop();

        buffer << "W" << id << ": Got work packet " << p.getID() << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        buffer << "W" << id << ": Processed work packet " << p.getID() << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}
