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
            not_empty.wait(lock, [this]{ return !backend.empty(); });
            value = backend.front();
            backend.pop();
        }
        // here we go!
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
