//玩家飞机类
#ifndef MYAIRCRAFT_H
#define MYAIRCRAFT_H

#include"otherAircraft.h"
#include"aircraft.h"
class MyAircraft : public Aircraft
{

private:
    int bulletPower;
    int power;
    int powerStand;
public:
    MyAircraft(int k=1);
    void explode();
    void move(double x, double y);
   int getBulletPower();
   void setBulletPower(int power);
   void bulletPowerAdd();
   void bulletPowerSub();

   void creatOtherAircraft();
    void otherAircraftClear(int i);
    void otherAircraftExplodeTimeOutWhether(int i);
    void powerAdd();
    void powerSub();
    int getPower();
    int getPowerStand();
     int speedJudge(int k);//得到相应等级所对应的速度
};
#endif // MYAIRCRAFT_H
