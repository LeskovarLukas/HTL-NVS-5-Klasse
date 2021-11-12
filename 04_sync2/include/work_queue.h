//WORK_QUEUE_H

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include "work_packet.h"

class WorkQueue {
private:
    std::queue<WorkPacket> queue;

public:
    const size_t queue_size;
    std::mutex queue_mutex;
    std::mutex print_mutex;
    std::condition_variable not_empty;
    std::condition_variable not_full;

    WorkQueue(size_t queue_size=1): queue_size{queue_size} {
        this->queue = std::queue<WorkPacket>();
    };
    void push(WorkPacket);
    WorkPacket pop();
    size_t size();
};
