//WORK_PACKET_H

#pragma once 

class WorkPacket
{
private:
    const int id;
public:
    WorkPacket(int id): id{id} {};

    int getID() const {
        return this->id;
    }
};