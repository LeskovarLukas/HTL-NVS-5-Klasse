//
// Created by Lukas Leskovar on 06.10.21.
//

#ifndef INC_02_THREADS_CAR_H
#define INC_02_THREADS_CAR_H

#include <string>

class Car {
private:
    std::string carType;

    void driveLaps();
public:
    Car(std::string carType);

    void operator()();

};


#endif //INC_02_THREADS_CAR_H
