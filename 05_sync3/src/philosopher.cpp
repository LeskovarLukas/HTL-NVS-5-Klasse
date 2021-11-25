#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include "Philosopher.h"
#include "utils.h"


void Philosopher::operator()(bool isLivelock)
{
    println("Philosopher", std::to_string(id), "is thinking...");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (true) {
        println("Philosopher", std::to_string(id), "attempts to get left fork");
        std::unique_lock<std::mutex> lck(Philosopher::leftForkSem_mtx);
        if (leftForkSem) {
            leftForkSem->aquire();
            if (leftForkSem->available_permits() == 0) {
                println("currently 1 left fork available");
            }
        }
        leftFork.lock();
        lck.unlock();

        println("Philosopher", std::to_string(id), "got left fork. Now he wants the right one...");
        std::this_thread::sleep_for(std::chrono::seconds(5));

        bool rightForkAvailable;
        if (isLivelock) {
            rightForkAvailable = rightFork.try_lock_for(std::chrono::seconds(3));
        } else {
            rightFork.lock();
            rightForkAvailable = true;
        }

        if (!rightForkAvailable) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            leftFork.unlock();

            println("Philosopher", std::to_string(id), "released left fork due to timeout getting the right one!");
            if (leftForkSem) {
                leftForkSem->release();
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else {
            println("Philosopher", std::to_string(id), "got right fork. Now he is eating...");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            println("Philosopher", std::to_string(id), "finished eating");

            leftFork.unlock();
            println("Philosopher", std::to_string(id), "released left fork");
            if (leftForkSem) {
                leftForkSem->release();
                println("currently", std::to_string(leftForkSem->available_permits() + 1), "left fork available");
            }
            
            rightFork.unlock();
            println( "Philosopher", std::to_string(id), "released right fork");

            println("Philosopher", std::to_string(id), "is thinking...");
            std::this_thread::sleep_for(std::chrono::seconds(1));       
        }
    }
}

// void Philosopher::println(const std::initializer_list<std::string>& text) {
//     std::lock_guard<std::mutex> lock(Philosopher::out_mtx);

//     for (auto& line : text) {
//         std::cout << line << " ";
//     }
//     std::cout << std::endl;
// }


//std::mutex Philosopher::out_mtx;

std::mutex Philosopher::leftForkSem_mtx;