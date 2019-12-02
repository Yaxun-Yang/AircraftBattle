//玩家子弹类
#ifndef MYBULLET_H
#define MYBULLET_H

#include "bullet.h"

class MyBullet :public Bullet
{
public:
    MyBullet(double x,double y,int k=1);
    ~MyBullet();
};

#endif // MYBULLET_H
