#include "myBullet.h"

MyBullet::MyBullet(double x,double y,int k):Bullet(x,y,k)
{
    setBulletPix(QPixmap(":/myBullet.png"));

}
MyBullet::~MyBullet()
{

}
