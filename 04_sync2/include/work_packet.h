//WORK_PACKET_H

#pragma once 

#include <iostream>

class WorkPacket
{
private:
    int id;
public:
    WorkPacket(int id): id{id} {};

    int getID() const {
        return id;
    }
};