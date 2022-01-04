#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};
  public:
    Pipe& operator<<(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!closed) {
            backend.push(value);
            not_empty.notify_one();
        }
        return *this;
    }
    
    Pipe& operator>>(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        if (!closed) {
            not_empty.wait_for(lock, std::chrono::milliseconds(500), [this]{ return !backend.empty(); });
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
};
#endif
