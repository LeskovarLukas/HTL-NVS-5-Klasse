#include <iostream>
#include <thread>
#include <sstream>
#include <random>
#include <iomanip>
#include "../include/work_queue.h"

void worker(int, WorkQueue&);


int main() {
    WorkQueue queue{};
    int counter = 0;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};

    std::thread t1(worker, 1, std::ref(queue));
    std::thread t2(worker, 2, std::ref(queue));
    std::thread t3(worker, 3, std::ref(queue));

    std::cout << std::setprecision(3);

    while (true)
    {
        int waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});

        std::lock_guard<std::mutex> lock(queue.queue_mutex);
        queue.push(WorkPacket(counter)); 

        std::cout << "B: Submitted work packet " << counter++ << " (" << waitTime / 1000.0 << "s)" << std::endl;

        queue.not_empty.notify_one();
    }
    
    t1.join();
    t2.join();

    return 0;
}


void worker(int id, WorkQueue& q) {
    std::ostringstream buffer;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};

    buffer << std::setprecision(3);

    while(true) {
        buffer << "W" << id << ": Want work packet" << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        std::unique_lock<std::mutex> lock(q.queue_mutex);
        q.not_empty.wait(lock);

        WorkPacket p = q.pop();
        std::cout << "W" << id << ": Got work packet " << p.getID() << std::endl;

        lock.unlock();

        int waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});

        buffer << "W" << id << ": Processed work packet " << p.getID() << " (" << waitTime / 1000.0 << "s)" << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}
