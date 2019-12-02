//战斗背景类
#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <QWidget>
#include <QPen>
#include <QBrush>

#include "global.h"
#include "myAircraft.h"
#include "otherAircraft.h"
#include "myBullet.h"
#include "otherBullet.h"

//生命值图标大小
#define HEALTH_LOGO_50 40
#define HEALTH_LOGO_20 30
#define HEALTH_LOGO_5 20
#define HEALTH_LOGO_1 10
#define HEALTH_LOGO_DISTANCE 40


class BattleWidget : public QWidget
{
    Q_OBJECT
private:

    bool pause;//是否按下暂停键
    bool music;//是否按下音乐键
    bool direction;//方向键选择控制
    int bullet;//子弹控制选择

    bool up;
    bool down;
    bool left;
    bool right;
    bool space;

    MyAircraft* myAircraft;

    QTimer * timer;
    int time1,time2,time3;//时间事件id记录函数
    //声音
    QSound* myAircraftHit;
    bool myAircraftHitPlayed;
    QSound* otherAircraftHit;
    bool otherAircraftHitPlayed;
    QMediaPlayer *groundBack;
    QMediaPlaylist *playerList;

    int numberOfOtherAircraft; //记录产生敌机的数量
    int numberOfOtherBullet;//记录产生敌机子弹的数量
    int numberOfMyBullet;//记录产生玩家子弹数量
    OtherAircraft * otherAircraft[1000];
    OtherBullet * otherBullet[10000];
    MyBullet * myBullet[10000];


    //右上角生命显示栏
    QLabel* health_50[5];
    QLabel* health_20[5];
    QLabel* health_5[5];
    QLabel* health_1[5];


    //右上角菜单栏
    QPushButton* pauseButton;//停止按钮
    QPushButton* mainMenuButton;//主菜单按钮
    QPushButton* musicButton;
    QHBoxLayout* layout;//右上方按钮的水平布局管理器
    //正上方分数显示
    int credit;//积分统计
    int mode;//模式等级


    QLabel* creditShow;//展示按钮

    QPixmap* logoPix;


public:
    //构造函数和析构函数
    BattleWidget(bool direction,bool music,int bullet,
                 int k,QWidget* mainMenuWidget ,QWidget *parent = 0);
    ~BattleWidget();

    int getCredit();
    int getMode();

 private:
    bool myBulletHitJudge(int i);//判断玩家子弹是否击中敌机
    bool otherBulletHitJudge(int i);//判断子弹是否击中玩家
    bool twoAircraftMeetJudge(int i);//判断玩家飞机与敌机是否相遇

    void myAircraftExplodeTimeOutWhether();//玩家飞机爆炸云消失倒计时
    void otherAircraftExplodeTimeOutWhether(int i);//敌机爆炸云消失倒计时

    void creatOtherAircraft();//产生敌机
    void creatOtherBullet(double x,double y,int power);//产生敌机子弹
    void creatMyBullet(double x,double y,int power=1);//产生玩家子弹
    
    void otherAircraftClear(int i);//清理敌机
    void otherBulletClear(int i);//清理敌机子弹
    void myBulletClear(int i);//清理玩家子弹

    void myAircraftMove();//玩家飞机移动的第二种解决方案

    //上方的图标们
    void howToShowHealth(int health);//随生命值变化的图标展示方案
    void howToShowPower(int power);//随能量值变化的展示方案
    void howToShowCredit();//积分展示方案
    void healthLabelCreat(int i, int k);
protected:
    //事件函数
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    void timerUpdate();

public slots:
    void theMusicButtonClicked();
    void pauseButtonClicked();
    void mainMenuButtonClicked();

signals:
    void gameOver();


};

#endif // BATTLEWIDGET_H
