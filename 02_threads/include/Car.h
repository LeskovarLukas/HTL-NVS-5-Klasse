//
// Created by Lukas Leskovar on 06.10.21.
//

#ifndef INC_02_THREADS_CAR_H
#define INC_02_THREADS_CAR_H

#include <string>

class Car {
private:
    std::string carType;
    int totalTime{};

    void driveLaps(int);
public:
    Car(std::string);

    void operator()(int);
    int getTotalTime();
    std::string toString();

};


#endif //INC_02_THREADS_CAR_H
