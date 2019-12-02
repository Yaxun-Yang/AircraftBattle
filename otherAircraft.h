//敌机类
#ifndef OTHERAIRCRAFT_H
#define OTHERAIRCRAFT_H

#include "aircraft.h"

class OtherAircraft : public Aircraft
{

public:
    OtherAircraft(int k=1);
    ~OtherAircraft();
    void explode();
};

#endif // OTHERAIRCRAFT_H
