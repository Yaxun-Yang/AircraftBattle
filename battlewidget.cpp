  #include "battleWidget.h"

BattleWidget::BattleWidget(bool direction,bool music,int bullet,
                           int k,QWidget* mainMenuWidget,QWidget *parent)
    : QWidget(parent)

{
    //页面一些量的初始化
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(WIDTH,HEIGHT);


    myAircraft=new MyAircraft(k);

    this->setFocus();

    logoPix=new QPixmap(":/logo.png");
    mode=k;
    this->music=music;
    this->direction=direction;
    this->bullet=bullet;

    //声音设置
    playerList = new QMediaPlaylist;
    playerList->setCurrentIndex(1);
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playerList->addMedia(QUrl::fromLocalFile("../sound/groundBack.mp3"));
    groundBack=new QMediaPlayer;
    groundBack->setPlaylist(playerList);

    myAircraftHit=new QSound("../sound/myAircraftHit.wav");
    myAircraftHitPlayed=false;
    otherAircraftHit=new QSound("../sound/otherAircraftHit_2.wav");
    otherAircraftHitPlayed=false;

    if(music)
    groundBack->play();//播放背景音乐


    pause= false;//用于判断画面是否暂停


    //初始化敌机子弹等的数量
    numberOfOtherAircraft=0;
    numberOfOtherBullet=0;
    numberOfMyBullet=0;
    
    //用于判断是否同时按下两个键
    up=false;
    left=false;
    right=false;
    down=false;
    space=false;

    //主菜单键的构建
    mainMenuButton = new QPushButton(this);
    mainMenuButton->setText(tr("Main Menu(&M)"));
    mainMenuButton->setIcon((QIcon)":/mainMenu.png");
    mainMenuButton->setStyleSheet(BUTTON_STYLE_3);
    mainMenuButton->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    connect(mainMenuButton,SIGNAL(clicked(bool)),mainMenuWidget
            ,SLOT(battleWidgetMainMenuButtonClicked()));
    connect(mainMenuButton,SIGNAL(clicked(bool)),this,SLOT(mainMenuButtonClicked()));
    //暂停按钮的构建
    pauseButton =new QPushButton(this);
    pauseButton->setText(tr("Pause(&P)"));
    pauseButton->setIcon((QIcon)":/pause.png");
    pauseButton->setStyleSheet(BUTTON_STYLE_3);
    pauseButton->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    connect(pauseButton,SIGNAL(clicked(bool)),this,SLOT(pauseButtonClicked()));

   //音乐按钮的构建
    musicButton =new QPushButton(this);
    musicButton->setText(tr("Music(&C)"));
    if(music)
    musicButton->setIcon((QIcon)":/music.png");
    else
    {
        musicButton->setIcon((QIcon)":/stopMusic.png");
    }
    musicButton->setStyleSheet(BUTTON_STYLE_3);
    musicButton->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    connect(musicButton,SIGNAL(clicked(bool)),this,SLOT(theMusicButtonClicked()));
    //右上方按钮的水平布局管理器的构建
    layout=new QHBoxLayout;
    layout->addWidget(musicButton);
    layout->addWidget(pauseButton);
    layout->addWidget(mainMenuButton);
    layout->setSpacing(5);
    layout->setContentsMargins(300,2,5,500);
    setLayout(layout);


    //左上方生命显示的构建

    for(int i=0;i<5;i++)
    {

        health_1[i]=NULL;
        health_5[i]=NULL;
        health_20[i]=NULL;
        health_50[i]=NULL;
    }
    howToShowHealth(myAircraft->getHealth());

    //初始积分和积分显示
    credit=0;
    creditShow=new QLabel(this);
    creditShow->setFont(QFont("FangSong",36,100));
    creditShow->setGeometry(200,0,100,40);
    howToShowCredit();


    //子弹速度、飞机速度等等与移动有关事件的控制器
    timer = new QTimer(this);
    timer->start(UPDATE_TIME);
    connect(timer, &QTimer::timeout, this, &BattleWidget::timerUpdate);

    connect(this,SIGNAL(gameOver()),mainMenuWidget,SLOT(newGameOver()));

    //创建一个计时器，负责按照规律定时创造子弹、敌机
    switch(myAircraft->getLevel())//生成敌机的间隔时间和产生子弹的时间间隔
    {
    case 1:
        time1=3*ONE_SECOND;
        time2=2*ONE_SECOND;
        time3=3*ONE_SECOND;
    break;
    case 2:
        time1=2.5*ONE_SECOND;
        time2=1.8*ONE_SECOND;
        time3=0.3*ONE_SECOND;
    break;
    case 3:
        time1 =2*ONE_SECOND;
        time2=1.5*ONE_SECOND;
        time3=0.5*ONE_SECOND;
    break;
    case 4:
        time1=1.5*ONE_SECOND;
        time2=1.2*ONE_SECOND;
        time3=0.8*ONE_SECOND;
    break;
    case 5:
        time1 =0.5*ONE_SECOND;
        time2=1*ONE_SECOND;
        time3=0.01*ONE_SECOND;
    break;
    case 6:
        time1 =0.5*ONE_SECOND;
        time2=0.8*ONE_SECOND;
        time3=0.01*ONE_SECOND;
    }
    time1=startTimer(time1);
    time2=startTimer(time2);
    time3=startTimer(time3);
}

BattleWidget::~BattleWidget()

{
    for(int i=0;i<10000;i++)
    {
        delete  myBullet[i] ;
        delete otherBullet[i];
    }
    for(int i=0;i<1000;i++)
    delete otherAircraft[i];
}

/*
 * 玩家飞机由键盘 上下左右 键控制方向
 * 在键盘事件中仅完成移动方向的标记，具体移动在时间事件中完成
*/
void BattleWidget::keyPressEvent(QKeyEvent *event)
//按键处理
{
    if (!myAircraft->getAlive()||pause)
        return;
    if(direction)
    switch (event->key())
    {
    case Qt::Key_W:
        up=true;
        event->accept();
        break;
    case Qt::Key_S:
        down=true;
        event->accept();
        break;
    case Qt::Key_A:
        left=true;
        event->accept();
        break;
    case Qt::Key_D:
        event->accept();
        right=true;
        break;
    default:
        event->ignore();
    }
    else
    {
        switch(event->key())
        {
        case Qt::Key_Up:
            up=true;
            event->accept();
            break;
        case Qt::Key_Down:
            down=true;
            event->accept();
            break;
        case Qt::Key_Left:
            left=true;
            event->accept();
            break;
        case Qt::Key_Right:
            event->accept();
            right=true;
            break;
        default:
            event->ignore();
        }


    }


    if(bullet==0)
    {
        switch(event->key())
        {
        case Qt::Key_Space:
           event->accept();
           space=true;
           break;
        default:
            event->ignore();
        }


    }
    else if(bullet==1)
    {
        switch(event->key())
        {
        case Qt::Key_Shift:
           event->accept();
           space=true;
           break;
        default:
            event->ignore();
        }


    }
    else if(bullet==2)
    {
        switch(event->key())
        {
        case Qt::Key_Enter:
           event->accept();
           space=true;
           break;
        default:
            event->ignore();
        }


    }
    else if(bullet==3)
    {
        switch(event->key())
        {
        case Qt::Key_Control:
           event->accept();
           space=true;
           break;
        default:
            event->ignore();
        }


    }
    else if(bullet==4)
    {
        switch(event->key())
        {
        case Qt::Key_Alt:
           event->accept();
           space=true;
           break;
        default:
            event->ignore();
        }


    }

    switch (event->key())
    {
    case Qt::Key_N:
        event->accept();
        myAircraft->bulletPowerSub();
        break;
    case Qt::Key_M:
        event->accept();
        myAircraft->bulletPowerAdd();
        break;
    default:
        event->ignore();
    }

}
void BattleWidget::keyReleaseEvent(QKeyEvent *event)
//释放键处理
{
    if(direction)
    {
        switch (event->key())
        {
        case Qt::Key_W:
            up=false;
            break;
        case Qt::Key_A:
            left=false;
            break;
        case Qt::Key_D:
            right=false;
            break;
        case Qt::Key_S:
            down=false;
            break;
        default:
            event->ignore();
        }
    }
    else
    {
        switch (event->key())
        {
        case Qt::Key_Up:
            up=false;
            break;
        case Qt::Key_Left:
            left=false;
            break;
        case Qt::Key_Right:
            right=false;
            break;
        case Qt::Key_Down:
            down=false;
            break;
        default:
            event->ignore();
        }
    }

    if((bullet==0&&event->key()==Qt::Key_Space)
    ||(bullet==1&&event->key()==Qt::Key_Shift)
    ||(bullet==2&&event->key()==Qt::Key_Enter)
    ||(bullet==3&&event->key()==Qt::Key_Control)
    ||(bullet==4&&event->key()==Qt::Key_Alt))
    {
        space=false;
    }
    else
    {
        event->ignore();
    }

}
void BattleWidget::paintEvent(QPaintEvent *)
//绘制图像
{

    //移动的第二种解决方案

    myAircraftMove();

    QPainter painter(this);
    QPen pen(Qt::gray,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QBrush brush(Qt::gray,Qt::SolidPattern);



    painter.setPen(pen);
    painter.drawRect(QRect(5,50,myAircraft->getPowerStand()*6,20));
    painter.setBrush(brush);
    painter.drawRect(QRect(5,50,myAircraft->getPower()*6,20));


    //判断是否开始爆炸倒计时
    if(!myAircraft->getAlive())
    {
        if(!myAircraftHitPlayed&&music)
        {
            myAircraftHit->play();
            myAircraftHitPlayed=true;
        }

        myAircraftExplodeTimeOutWhether();
    }
//qDebug("%lf,%lf\n",myAircraft->getXpos(),myAircraft->getYpos());

    //绘制玩家飞机
    painter.drawPixmap(myAircraft->getXpos(),myAircraft->getYpos(),
    MY_AIRCRAFT_SIZE,MY_AIRCRAFT_SIZE,myAircraft->getAircraftPix());


    for(int i=0;i<numberOfOtherAircraft;i++)
   if(otherAircraft[i]!=NULL)
    {
//       qDebug("%d,%lf,%lf,%d\n",i,myAircraft->otherAircraft[i]->getXpos()
//              ,myAircraft->otherAircraft[i]->getYpos()
//              ,myAircraft->otherAircraft[i]->getSpeed());

    //绘制敌机
        painter.drawPixmap(
                    otherAircraft[i]->getXpos()
                    ,otherAircraft[i]->getYpos()
                    ,OTHER_AIRCRAFT_SIZE
                    ,OTHER_AIRCRAFT_SIZE
                    ,otherAircraft[i]->getAircraftPix()
                            );
        if(otherAircraft[i]->getAlive()&&twoAircraftMeetJudge(i))
        {
            myAircraft->healthSub(otherAircraft[i]->getLevel());
            howToShowHealth(myAircraft->getHealth());
            otherAircraft[i]->healthSub(otherAircraft[i]->getLevel());
        }
        //如果敌机存活则保证不停向前移动
        if(otherAircraft[i]->getAlive())
        otherAircraft[i]->
                move(0,otherAircraft[i]->getSpeed());
        else
        {
            if(!otherAircraftHitPlayed&&music)
            {
                otherAircraftHit->play();
                otherAircraftHitPlayed=true;
            }

            otherAircraftExplodeTimeOutWhether(i);
        }
        //避免空指针的调用
        if(otherAircraft[i]==NULL)
        continue;




     /*
            //测试敌机爆炸情况
        if(i==4&&myAircraft->otherAircraft[i]->getYpos()>=200)
        myAircraft->otherAircraft[i]->healthSub();
     */

            if(otherAircraft[i]->getYpos()>=HEIGHT)
        {
          otherAircraftClear(i);
           // qDebug("%d\n",i);
        }


    }

    for(int i=0;i<numberOfMyBullet;i++)
        if(myBullet[i]!=NULL)
    {
        painter.drawPixmap(myBullet[i]->getXpos(),myBullet[i]->getYpos(),
                           MY_BULLET_WIDTH,MY_BULLET_HEIGHT,myBullet[i]->getBulletPix());

       myBullet[i]->move(0,-myBullet[i]->getSpeed());

        if(myBulletHitJudge(i)||myBullet[i]->getYpos()<-MY_BULLET_HEIGHT)
        {
            myBulletClear(i);
        }
    }

    for(int i=0;i<numberOfOtherBullet;i++)
    if(otherBullet[i]!=NULL)
    {
        painter.drawPixmap(otherBullet[i]->getXpos(),otherBullet[i]->getYpos(),
        OTHER_BULLET_WIDTH,OTHER_BULLET_HEIGHT,otherBullet[i]->getBulletPix());

        otherBullet[i]->move(0,otherBullet[i]->getSpeed());
        if(otherBulletHitJudge(i)||otherBullet[i]->getYpos()>HEIGHT)
        {
            otherBulletClear(i);
        }

    }

}
void BattleWidget::timerEvent(QTimerEvent *event)
//定时产生敌机和敌机子弹+回复能量
{

    if(!pause&&event->timerId()==time1)
    {
        creatOtherAircraft();
    }
    if(!pause&&event->timerId()==time2)
    {
        for(int i=0;i<numberOfOtherAircraft;i++)
        if(otherAircraft[i]!=NULL&&otherAircraft[i]->getAlive())
        {
            creatOtherBullet(
            otherAircraft[i]->getXpos()+(OTHER_AIRCRAFT_SIZE-OTHER_BULLET_WIDTH)/2
            ,otherAircraft[i]->getYpos(),otherAircraft[i]->getLevel());

        }
    }
    if(!pause&&event->timerId()==time3&&myAircraft->getPower()<myAircraft->getPowerStand())
    {
        myAircraft->powerAdd();
    }


}
void BattleWidget::timerUpdate()
{
    if(!pause)
    {
        this->update();
    }

}

void BattleWidget::theMusicButtonClicked()
//按下音乐按钮以后
{
    if(music)
        {
            music=false;
            musicButton->setIcon(QIcon(":/stopMusic.png"));
            musicButton->setText(tr("NoMusic(&C)"));
            groundBack->pause();
        }
        else
        {
            music=true;
            musicButton->setIcon(QIcon(":/music.png"));
            musicButton->setText(tr("Music(&C)"));
            myAircraftHit->stop();
            otherAircraftHit->stop();
            groundBack->play();
        }
    this->setFocus();
}

void BattleWidget::pauseButtonClicked()
//按下暂停键之后
{
    if(pause)
    {
        pause=false;
        pauseButton->setIcon(QIcon(":/pause.png"));
        pauseButton->setText(tr("Pause(&P)"));
        groundBack->play();
        this->setFocus();
    }
    else
    {
        pause=true;

        pauseButton->setIcon(QIcon(":/continue.png"));
        pauseButton->setText(tr("Continue(&P)"));
        myAircraftHit->stop();
        otherAircraftHit->stop();
        groundBack->pause();
        this->setFocus();
    }

}
void BattleWidget::mainMenuButtonClicked()

{
    if(!pause)
    {
        pause=true;
        pauseButton->setIcon(QIcon(":/continue.png"));
        pauseButton->setText(tr("Continue(&P)"));
        groundBack->stop();
        this->setFocus();
    }
}

void BattleWidget::myAircraftExplodeTimeOutWhether()
//玩家飞机爆炸云残存时间判断
{
    myAircraft->explodeTimeSub();
    if(myAircraft->getExplodeTime()<=0)
    {   
        myAircraft->~MyAircraft();
        myAircraftHitPlayed=false;
        groundBack->stop();
        emit gameOver();
    }
}
void BattleWidget::otherAircraftExplodeTimeOutWhether(int i)
//敌机爆炸云残存事件判断
{

    otherAircraft[i]->explodeTimeSub();
    if(otherAircraft[i]->getExplodeTime()<=0)
    {
        otherAircraftHitPlayed=false;
        otherAircraftClear(i);
    }

}

bool BattleWidget::otherBulletHitJudge(int i)
//敌机子弹是否击中目标判断
{
    if(myAircraft->getXpos()<=otherBullet[i]->getXpos()+OTHER_BULLET_WIDTH
    &&myAircraft->getXpos()+MY_AIRCRAFT_SIZE>=otherBullet[i]->getXpos()
    &&otherBullet[i]->getYpos()+OTHER_BULLET_HEIGHT>myAircraft->getYpos()
    &&otherBullet[i]->getYpos()<myAircraft->getYpos()+MY_AIRCRAFT_SIZE)
    {

        myAircraft->healthSub(otherBullet[i]->getPower());
        howToShowHealth(myAircraft->getHealth());
        return true;
    }
       return false;
}
bool BattleWidget::myBulletHitJudge(int i)
//玩家子弹是否击中目标判断
{
    for(int j=0;j<numberOfOtherAircraft;j++)
    if(otherAircraft[j]!=NULL&&otherAircraft[j]->getAlive()
    &&myBullet[i]->getXpos()<=otherAircraft[j]->getXpos()+OTHER_AIRCRAFT_SIZE
    &&myBullet[i]->getXpos()+MY_BULLET_WIDTH>=otherAircraft[j]->getXpos()
    &&myBullet[i]->getYpos()<=otherAircraft[j]->getYpos()+OTHER_AIRCRAFT_SIZE
    &&myBullet[i]->getYpos()+MY_BULLET_HEIGHT>=otherAircraft[j]->getYpos())
      {
        if(otherAircraft[j]->getHealth()<=myBullet[i]->getPower())
        {
            credit+=otherAircraft[j]->getLevel();
            howToShowCredit();
        }
        otherAircraft[j]->healthSub(myBullet[i]->getPower());
        return true;
    }
    return false;
}
bool BattleWidget::twoAircraftMeetJudge(int i)
//玩家飞机与敌机是否相遇
{
    if(otherAircraft[i]->getXpos()<myAircraft->getXpos()+MY_AIRCRAFT_SIZE
    &&otherAircraft[i]->getXpos()+OTHER_AIRCRAFT_SIZE>myAircraft->getXpos()
    &&otherAircraft[i]->getYpos()<myAircraft->getYpos()+MY_AIRCRAFT_SIZE
    &&otherAircraft[i]->getYpos()+OTHER_AIRCRAFT_SIZE>myAircraft->getYpos())
    {
        credit+=otherAircraft[i]->getLevel();
        return true;
    }
    return false;
}

void BattleWidget::creatOtherAircraft()
//产生敌机
{
    int rand=(qrand()%(myAircraft->getLevel()+1))+1;
    otherAircraft[numberOfOtherAircraft++]=new OtherAircraft(rand);
}
void BattleWidget::creatMyBullet(double x, double y, int power)
//产生玩家子弹
{
    if(myAircraft->getPower()>0)
    {
        myBullet[numberOfMyBullet++]=new MyBullet(x,y,power);
        myAircraft->powerSub();
    }

}
void BattleWidget::creatOtherBullet(double x,double y,int power)
//产生敌机子弹
{
    otherBullet[numberOfOtherBullet++]=new OtherBullet(x,y,power);
}
void BattleWidget::otherAircraftClear(int i)
//清理不再出现的敌机对象
{
   // qDebug("%d\n",i);
    otherAircraft[i]->~OtherAircraft();
    otherAircraft[i]=NULL;
}
void BattleWidget::myBulletClear(int i)
//清理不再出现的玩家子弹
{
    myBullet[i]->~MyBullet();
    myBullet[i]=NULL;
}
void BattleWidget::otherBulletClear(int i)
//清理不再出现的敌机子弹
{
    otherBullet[i]->~OtherBullet();
    otherBullet[i]=NULL;
}

void BattleWidget::myAircraftMove()
//玩家飞机移动方式
{
    if(!myAircraft->getAlive())
        return;
    if(space)
    creatMyBullet(myAircraft->getXpos()+(MY_AIRCRAFT_SIZE-MY_BULLET_WIDTH)/2
                      ,myAircraft->getYpos(),myAircraft->getBulletPower());


    if((up&&down&&left&&!right)||(!up&&!down&&left&&!right))//向左
    {
        myAircraft->move(-myAircraft->getSpeed(),0);
    }
    else if((up&&down&&!left&&right)||(!up&&!down&&!left&&right))//向右
    {
         myAircraft->move(myAircraft->getSpeed(),0);
    }
    else if((up&&!down&&left&&right)||(up&&!down&&!left&&!right))//向上
    {
        myAircraft->move(0,-myAircraft->getSpeed());
    }
    else if(up&&!down&&left&&!right)//向左上
    {
        myAircraft->move(-0.7*myAircraft->getSpeed(),-0.7*myAircraft->getSpeed());
    }
    else if(up&&!down&&!left&&right)//向右上
    {
        myAircraft->move(0.7*myAircraft->getSpeed(),-0.7*myAircraft->getSpeed());
    }
    else if ((!up&&down&&left&&right)||(!up&&down&&!left&&!right))//向下
    {
        myAircraft->move(0,myAircraft->getSpeed());
    }
    else if(!up&&down&&left&&!right)//向左下
    {
        myAircraft->move(-0.7*myAircraft->getSpeed(),0.7*myAircraft->getSpeed());
    }
    else if(!up&&down&&!left&&right)//向右下
    {
        myAircraft->move(0.7*myAircraft->getSpeed(),0.7*myAircraft->getSpeed());
    }
}

void BattleWidget::howToShowCredit()
//积分展示方案
{
    QString str=QString::number(credit,10);
    creditShow->setText(str);
}
void BattleWidget::howToShowHealth(int health)
//生命值图标展示方案
{
    health=health>=0?health:0;
    int healthValue[]={50,20,5,1};
   int   distance=0;//记录是此时生命图标栏的第几个图标
    for(int i=0;i<4;i++)
    {
        for(int k=0;k<5;k++)
        {
            while(health/healthValue[i])//如果需要的图标不存在创建它
            {
                health-=healthValue[i];
                switch (healthValue[i])
                {
                case 50:
                    if(health_50[k]==NULL)
                    {
                        health_50[k]=new QLabel(this);
                        health_50[k]->setGeometry(distance
                                                  ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_50
                                                  ,HEALTH_LOGO_50,HEALTH_LOGO_50);
                        logoPix->scaled(health_50[k]->size(),Qt::KeepAspectRatio);
                        health_50[k]->setPixmap(*logoPix);
                        health_50[k]->setScaledContents(true);
                        health_50[k]->show();
                    }
                    else
                    {
                        health_50[k]->setGeometry(distance
                                                  ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_50
                                                  ,HEALTH_LOGO_50,HEALTH_LOGO_50);
                    }
                    distance+=HEALTH_LOGO_DISTANCE;
                    break;
                case 20:
                    if(health_20[k]==NULL)
                    {
                        health_20[k]=new QLabel(this);
                        health_20[k]->setGeometry(distance
                                                  ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_20
                                                  ,HEALTH_LOGO_20,HEALTH_LOGO_20);
                        logoPix->scaled(health_20[k]->size(),Qt::KeepAspectRatio);
                        health_20[k]->setPixmap(*logoPix);
                        health_20[k]->setScaledContents(true);
                        health_20[k]->show();
                    }
                    else
                    {
                        health_20[k]->setGeometry(distance
                                                  ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_20
                                                  ,HEALTH_LOGO_20,HEALTH_LOGO_20);
                    }
                    distance+=HEALTH_LOGO_DISTANCE-10;
                    break;
                case 5:
                    if(health_5[k]==NULL)
                    {
                        health_5[k]=new QLabel(this);
                        health_5[k]->setGeometry(distance
                                                 ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_5
                                                 ,HEALTH_LOGO_5,HEALTH_LOGO_5);
                        logoPix->scaled(health_5[k]->size(),Qt::KeepAspectRatio);
                        health_5[k]->setPixmap(*logoPix);
                        health_5[k]->setScaledContents(true);
                        health_5[k]->show();
                    }
                    else
                    {
                        health_5[k]->setGeometry(distance
                                                 ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_5
                                                 ,HEALTH_LOGO_5,HEALTH_LOGO_5);
                    }
                    distance+=HEALTH_LOGO_DISTANCE-20;
                    break;
                case 1:
                    if(health_1[k]==NULL)
                    {
                        health_1[k]=new QLabel(this);
                        health_1[k]->setGeometry(distance
                                                 ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_1
                                                 ,HEALTH_LOGO_1,HEALTH_LOGO_1);
                        logoPix->scaled(health_1[k]->size(),Qt::KeepAspectRatio);
                        health_1[k]->setPixmap(*logoPix);
                        health_1[k]->setScaledContents(true);
                        health_1[k]->show();
                    }
                    else
                    {
                        health_1[k]->setGeometry(distance
                                                 ,HEALTH_LOGO_DISTANCE-HEALTH_LOGO_1
                                                 ,HEALTH_LOGO_1,HEALTH_LOGO_1);
                    }
                    distance+=HEALTH_LOGO_DISTANCE-30;
                    break;
                }
                k++;
            }
           switch(healthValue[i])//如果不需要的图标存在，清除它
           {
           case 50:
               if(health_50[k]!=NULL)
               {
                   health_50[k]->~QLabel();
                   health_50[k]=NULL;
               }
               break;
           case 20:
               if(health_20[k]!=NULL)
               {
                   health_20[k]->~QLabel();
                   health_20[k]=NULL;
               }
               break;
           case 5:
               if(health_5[k]!=NULL)
               {
                   health_5[k]->~QLabel();
                   health_5[k]=NULL;
               }
               break;
           case 1:
               if(health_1[k]!=NULL)
               {
                   health_1[k]->~QLabel();
                   health_1[k]=NULL;
               }
               break;
           }
        }


    }
}

int BattleWidget::getCredit()
//返回积分值
{
    return credit;
}
int BattleWidget::getMode()
//返回模式
{
    return mode;
}


