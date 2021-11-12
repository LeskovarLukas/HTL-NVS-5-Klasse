#include <iostream>
#include <thread>
#include <sstream>
#include <random>
#include <iomanip>
#include "../include/work_queue.h"

void worker(int, WorkQueue&);


int main() {
    WorkQueue q{};
    int counter = 0;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};
    std::ostringstream buffer;


    std::thread t1(worker, 1, std::ref(q));
    std::thread t2(worker, 2, std::ref(q));
    std::thread t3(worker, 3, std::ref(q));

    buffer << std::setprecision(3);

    while (true)
    {
        buffer << "B: Waiting to submit work packet " << counter << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        int waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});

        std::unique_lock<std::mutex> lock(q.queue_mutex);
        std::cout << q.size() << std::endl;
        std::cout << q.queue_size << std::endl;
        q.not_full.wait(lock, [&] { return q.size() < q.queue_size; });

        q.push(WorkPacket(counter)); 

        buffer << "B: Submitted work packet " << counter++ << " (" << waitTime / 1000.0 << "s)" << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        q.not_empty.notify_one();
        lock.unlock();
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
        q.not_empty.wait(lock, [&] { return q.size() > 0; });


        WorkPacket p = q.pop();
        buffer << "W" << id << ": Got work packet " << p.getID() << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");

        if (q.size() == q.queue_size - 1) {
            q.not_full.notify_one();
        }

        lock.unlock();

        int waitTime = dis(gen) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds{waitTime});

        buffer << "W" << id << ": Processed work packet " << p.getID() << " (" << waitTime / 1000.0 << "s)" << std::endl;
        std::cout << buffer.str() << std::flush;
        buffer.str("");
    }
}
