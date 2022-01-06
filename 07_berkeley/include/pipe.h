#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
    long latency;

  public:
    Pipe& operator<<(T value) {

        auto send_future = std::async(&Pipe::send, this, value);
        send_future.wait();
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!closed) {
            not_empty.wait(lock, [this]{ return !backend.empty(); });
            value = backend.front();
            backend.pop();
        }
        
        return *this;
    }

    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
    }
    
    explicit operator bool() {
        std::lock_guard<std::mutex> lock(mtx);
        return !closed;
    }

    void set_latency(long latency) {
        this->latency = latency;
    }

  private:

    void send(T value) {
        std::this_thread::sleep_for(std::chrono::milliseconds(latency));
        std::unique_lock<std::mutex> lock(mtx);
        backend.push(value);
        not_empty.notify_one();
    }
};
#endif
