//子弹基类
#ifndef BULLET_H
#define BULLET_H

#include "global.h"
#include "myAircraft.h"
#include "otherAircraft.h"

class Bullet
{
private:
    double xpos,ypos;
    QPixmap bulletPix;
    int speed;
    int power;
public:
    Bullet(double x,double y,int k=1);
    ~Bullet();
    void move (double x,double y);
    double getXpos();
    double getYpos();
    void setBulletPix(QPixmap bulletPix);
    QPixmap getBulletPix();
    void setSpeed(int speed);
    int  getSpeed();
    void setPower(int power);
    int getPower();

};

#endif // BULLET_H
