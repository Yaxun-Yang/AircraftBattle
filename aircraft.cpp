#include "aircraft.h"

Aircraft::Aircraft()
{
    alive=true;
    explodeTime=EXPLODE_TIME;
}
Aircraft::~Aircraft()
{

}

void Aircraft::move(double x, double y)
{
    xpos+=x;
    ypos+=y;
}
int Aircraft::getLevel()
{
    return level;
}
void Aircraft::setAircraftPix(QPixmap aircraftPix)
{
    this->aircraftPix=aircraftPix;
}
QPixmap Aircraft::getAircraftPix()
{
    return aircraftPix;
}
void Aircraft::setLevel(int level)
{
    this->level=level;
}
double Aircraft::getXpos()
{
    return xpos;
}
double Aircraft::getYpos()
{
    return ypos;
}
void Aircraft::setXpos(double xpos)
{
    this->xpos=xpos;
}
void Aircraft::setYpos(double ypos)
{
    this->ypos=ypos;
}
void Aircraft::setSpeed(int speed)
{
    this->speed=speed;
}
int Aircraft::getSpeed()
{
    return speed;
}
void Aircraft::setAlive(bool alive)
{
    this->alive=alive;
}
bool Aircraft::getAlive()
{
    return alive;
}
void Aircraft::setHealth(int health)
{
    this->health=health;
}
void Aircraft::healthAdd(int k)
{
    health+=k;
}
void Aircraft::healthSub(int k)
{
    health-=k;
    if(health<=0&&alive==true )
        explode();
}
int Aircraft::getHealth()
{
    return health;
}
void Aircraft::explodeTimeSub()
{
   explodeTime=explodeTime-UPDATE_TIME;
}
int Aircraft::getExplodeTime()
{
    return explodeTime;
}
void Aircraft::hitByBullet(int power)
{
    healthSub(power);
}

