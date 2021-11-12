
#include <iostream>
#include "../include/work_queue.h"

void WorkQueue::push(WorkPacket packet) {
    this->queue.push(packet);
}

WorkPacket WorkQueue::pop() {
   
    WorkPacket packet = this->queue.front();
    this->queue.pop();

    return packet;
}

size_t WorkQueue::size() {
    return queue.size();
}