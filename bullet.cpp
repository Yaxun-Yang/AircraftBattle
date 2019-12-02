#include "bullet.h"

Bullet::Bullet(double x,double y,int k)
{
    power=k;
    xpos=x;
    ypos=y;
    speed=BULLET_SPEED;
}
void Bullet::move(double x, double y)
{
    xpos+=x;
    ypos+=y;
}
double Bullet::getXpos()
{
    return xpos;
}
double Bullet::getYpos()
{
    return ypos;
}
void Bullet::setBulletPix(QPixmap bulletPix)
{
    this->bulletPix=bulletPix;
}
QPixmap Bullet::getBulletPix()
{
    return bulletPix;
}
void Bullet::setPower(int power)
{
    this->power=power;
}
int Bullet::getPower()
{
    return power;
}
void Bullet::setSpeed(int speed)
{
    this->speed=speed;
}
int Bullet::getSpeed()
{
    return speed;
}
Bullet::~Bullet()
{

}
