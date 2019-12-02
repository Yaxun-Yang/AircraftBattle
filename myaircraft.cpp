#include "myAircraft.h"

MyAircraft::MyAircraft(int k)
{
    bulletPower=1;

     setSpeed(speedJudge(k));
    setLevel(k);
    switch(k)
    {
        case 1:
        setHealth(1);
        power=5;
        powerStand=5;
        break;
        case 2:
        setHealth(50);
        power=20;
        powerStand=20;
        break;
        case 3:
        setHealth(30);
        power=20;
        powerStand=20;
        break;
        case 4:
        setHealth(30);
        power=20;
        powerStand=20;
        break;
        case 5:
        setHealth(100);
        power=100;
        powerStand=100;
        break;
    }
    setAircraftPix(QPixmap(":/myAircraft.png"));
    setXpos((WIDTH-MY_AIRCRAFT_SIZE)/2);
    setYpos(HEIGHT-MY_AIRCRAFT_SIZE);
}

void MyAircraft:: explode()
{
    setAircraftPix(QPixmap(":/myExplode.png"));
    setAlive(false);
}

void MyAircraft::move(double x, double y)
{
    if(getXpos()+x<=WIDTH-MY_AIRCRAFT_SIZE+OTHER_AIRCRAFT_SIZE&&
            getXpos()+x>=-OTHER_AIRCRAFT_SIZE&&
            getYpos()+y<=HEIGHT-MY_AIRCRAFT_SIZE&&getYpos()+y>=0)
        Aircraft::move(x,y);
}

int MyAircraft::getBulletPower()
{
    return bulletPower;
}

void MyAircraft::setBulletPower(int power)
{
    if(power>getLevel())
        bulletPower=getLevel();
    else if(power<1)
        bulletPower=1;
    else
    bulletPower=power;
}

void MyAircraft::bulletPowerAdd()
{
    if(bulletPower+1<getLevel())
    bulletPower++;
}

void MyAircraft::bulletPowerSub()
{
    if(bulletPower-1>0)
    {
        bulletPower--;
    }
}

int MyAircraft::speedJudge(int k)
{
    switch (k)
    {
    case 1:
        return  5;
    case 2:
        return 8;
    case 3:
        return 10;
    case 4:
        return 12;
    case 5:
        return 15;
     default:
        return 18;
    }
}
void MyAircraft::powerAdd()
{
    power++;
}
void MyAircraft::powerSub()
{
    power--;
}
int MyAircraft::getPower()
{
    return power;
}
int MyAircraft::getPowerStand()
{
    return powerStand;
}
