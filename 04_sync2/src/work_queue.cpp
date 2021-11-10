#include "../include/work_queue.h"

WorkQueue::WorkQueue() {
    this->queue = std::queue<WorkPacket>();
}

void WorkQueue::push(WorkPacket packet) {
    this->queue.push(packet);
}

WorkPacket WorkQueue::pop() {
    WorkPacket packet = this->queue.front();
    this->queue.pop();
    return packet;
}