//飞机基类
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "global.h"

class Aircraft
{
private:
    double xpos;
    double ypos;//飞机坐标
    bool alive=true;//是否存活
    int speed;//飞行速度
    int health;//生命值
    int level;//飞机等级
    QPixmap aircraftPix;//飞机图片
    int explodeTime;//爆炸云停留倒计时
public:
    Aircraft();
    virtual ~Aircraft();

    int getSpeed();
    void setSpeed(int speed);
    bool getAlive();
    void setAlive(bool alive);
    double getXpos();
    void setXpos(double xpos);
    double getYpos();
    void setYpos(double ypos);
    int getLevel();
    void setAircraftPix(QPixmap aircraftPix);
    QPixmap getAircraftPix();
    void setLevel(int level);
    int getHealth();
    void setHealth(int health);
    void healthAdd(int k=1);//生命值加
    void healthSub(int k=1);//生命值减
    void explodeTimeSub();
    int getExplodeTime();

    void hitByBullet(int power);//被击中
    virtual void explode()=0;//爆炸
    virtual void move(double x,double y);//移动


};

#endif // AIRCRAFT_H
