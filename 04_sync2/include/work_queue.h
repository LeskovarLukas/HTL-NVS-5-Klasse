//WORK_QUEUE_H

#pragma once

#include <queue>
#include "work_packet.h"

class WorkQueue {
private:
    std::queue<WorkPacket> queue;

public:
    WorkQueue();
    void push(WorkPacket work);
    WorkPacket pop();
};
