//敌机子弹类
#ifndef OTHERBULLET_H
#define OTHERBULLET_H

#include "bullet.h"

class OtherBullet: public Bullet
{
public:
    OtherBullet(double x,double y,int k);
    ~OtherBullet();
};

#endif // OTHERBULLET_H
