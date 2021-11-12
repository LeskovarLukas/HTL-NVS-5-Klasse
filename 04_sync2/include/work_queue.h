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
    std::mutex queue_mutex;
    std::condition_variable not_empty;

    WorkQueue();
    void push(WorkPacket work);
    WorkPacket pop();
};
