#include "readMeWidget.h"

ReadMeWidget::ReadMeWidget(QWidget* mainMenuWidget,bool direction,
        bool music,int bullet, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(WIDTH,HEIGHT);

    this->bullet=bullet;

    //回到主菜单按钮
    mainMenuButton= new QPushButton(tr("Main Menu"),this);
    mainMenuButton->setIcon(QIcon(":/mainMenu.png"));
    mainMenuButton->setStyleSheet(BUTTON_STYLE_3);
    mainMenuButton->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    mainMenuButton->setGeometry(530,20,150,40);
    connect(mainMenuButton,SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(readMeWidgetMainMenuButtonClicked()));
    //主题设置
    title=new QLabel(this);
    title->setFont(QFont("FangSong",24,100));
    title->setGeometry(100,60,500,40);
    title->setText("Welcome To Aircraft Battle");
    //副标题设置
    subTitle=new QLabel(this);
    subTitle->setFont(QFont("FangSong",16,80));
    subTitle->setGeometry(250,100,450,40);
    subTitle->setText("—— you can set your preferences");
    //方向设置
    text1=new QLabel(this);
    text1->setFont(QFont("Microsoft",12,50));
    text1->setGeometry(20,150,230,30);
    text1->setText("For direction control:");

    picture1=new QLabel(this);
    picture1->setGeometry(60,200,90,60);
    QPixmap picture_1(":/direction_2.png");
    picture_1.scaled(picture1->size(),Qt::KeepAspectRatioByExpanding);
    picture1->setPixmap(picture_1);
    picture1->setScaledContents(true);

    direction_1_Choose= new QPushButton(tr("I prefer this"),this);
    direction_1_Choose->setIcon(QIcon(":/prefer.png"));
    direction_1_Choose->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    direction_1_Choose->setGeometry(20,280,180,30);
    connect(direction_1_Choose,SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(direction_1_Clicked()));
    connect(direction_1_Choose,SIGNAL(clicked(bool)),this
        ,SLOT(direction_1_Clicked()));

    picture2=new QLabel(this);
    picture2->setGeometry(60,350,90,60);
    QPixmap picture_2(":/direction_1.png");
    picture_2.scaled(picture2->size(),Qt::KeepAspectRatioByExpanding);
    picture2->setPixmap(picture_2);
    picture2->setScaledContents(true);

    direction_2_Choose= new QPushButton(tr("I prefer this"),this);
    direction_2_Choose->setIcon(QIcon(":/prefer.png"));
    direction_2_Choose->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    direction_2_Choose->setGeometry(20,430,180,30);
    connect(direction_2_Choose,SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(direction_2_Clicked()));
    connect(direction_2_Choose,SIGNAL(clicked(bool)),this
        ,SLOT(direction_2_Clicked()));
    //是否播放音乐
    text2=new QLabel(this);
    text2->setFont(QFont("Microsoft",12,50));
    text2->setGeometry(250,150,230,30);
    text2->setText("Do you need music ?");

    music_1_Choose= new QPushButton(tr("Yes"),this);
    music_1_Choose->setIcon(QIcon(":/submit.png"));
    music_1_Choose->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    music_1_Choose->setGeometry(240,200,200,30);
    connect(music_1_Choose,SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(music_1_Clicked()));
    connect(music_1_Choose,SIGNAL(clicked(bool)),this
        ,SLOT(music_1_Clicked()));

    music_2_Choose= new QPushButton(tr(" No"),this);
    music_2_Choose->setIcon(QIcon(":/cancel.png"));
    music_2_Choose->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
    music_2_Choose->setGeometry(240,250,200,30);
    connect(music_2_Choose,SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(music_2_Clicked()));
    connect(music_2_Choose,SIGNAL(clicked(bool)),this
        ,SLOT(music_2_Clicked()));

    //发射子弹键控制
    text3=new QLabel(this);
    text3->setFont(QFont("Microsoft",12,50));
    text3->setGeometry(480,150,230,30);
    text3->setText("Which key do you prefer");

    text4=new QLabel(this);
    text4->setFont(QFont("Microsoft",12,50));
    text4->setGeometry(480,170,230,30);
    text4->setText("to fire the bullet with ?");




    bulletChoose[0]= new QPushButton(tr("Space"),this);
    connect(bulletChoose[0],SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(bullet_0_Clicked()));
    connect(bulletChoose[0],SIGNAL(clicked(bool)),this
        ,SLOT(bullet_0_Clicked()));

    bulletChoose[1]= new QPushButton(tr("Shift"),this);
    connect(bulletChoose[1],SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(bullet_1_Clicked()));
    connect(bulletChoose[1],SIGNAL(clicked(bool)),this
        ,SLOT(bullet_1_Clicked()));


    bulletChoose[2]= new QPushButton(tr("Enter"),this);
    connect(bulletChoose[2],SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(bullet_2_Clicked()));
    connect(bulletChoose[2],SIGNAL(clicked(bool)),this
        ,SLOT(bullet_2_Clicked()));


    bulletChoose[3]= new QPushButton(tr(" Ctrl"),this);
    connect(bulletChoose[3],SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(bullet_3_Clicked()));
    connect(bulletChoose[3],SIGNAL(clicked(bool)),this
        ,SLOT(bullet_3_Clicked()));

    bulletChoose[4]= new QPushButton(tr(" Alt "),this);
    connect(bulletChoose[4],SIGNAL(clicked(bool)),mainMenuWidget
        ,SLOT(bullet_4_Clicked()));
    connect(bulletChoose[4],SIGNAL(clicked(bool)),this
        ,SLOT(bullet_4_Clicked()));



    for(int i=0;i<5;i++)
    {
        bulletChoose[i]->setIcon(QIcon(":/bullets.png"));
        bulletChoose[i]->setIconSize(QSize(BUTTON_ICON_SIZE_3,BUTTON_ICON_SIZE_3));
        bulletChoose[i]->setStyleSheet(BUTTON_STYLE_3);
        bulletChoose[i]->setGeometry(480,230+60*i,200,30);
    }



    picture3=new QLabel(this);
    picture3->setGeometry(240,340,190,190);
    QPixmap picture_3(":/logo.png");
    picture_3.scaled(picture3->size(),Qt::KeepAspectRatioByExpanding);
    picture3->setPixmap(picture_3);
    picture3->setScaledContents(true);


    //默认选中设置
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_4);
    if(music)
    {
        music_1_Choose->setStyleSheet(BUTTON_STYLE_4);
        music_2_Choose->setStyleSheet(BUTTON_STYLE_3);
    }
    else
    {
        music_2_Choose->setStyleSheet(BUTTON_STYLE_4);
        music_1_Choose->setStyleSheet(BUTTON_STYLE_3);
    }
    if(direction)
    {
        direction_1_Choose->setStyleSheet(BUTTON_STYLE_4);
        direction_2_Choose->setStyleSheet(BUTTON_STYLE_3);
    }
    else
    {
        direction_2_Choose->setStyleSheet(BUTTON_STYLE_4);
        direction_1_Choose->setStyleSheet(BUTTON_STYLE_3);
    }

}
void ReadMeWidget::direction_1_Clicked()
{
     direction_1_Choose->setStyleSheet(BUTTON_STYLE_4);
     direction_2_Choose->setStyleSheet(BUTTON_STYLE_3);
}
void ReadMeWidget::direction_2_Clicked()
{
    direction_2_Choose->setStyleSheet(BUTTON_STYLE_4);
    direction_1_Choose->setStyleSheet(BUTTON_STYLE_3);
}
void ReadMeWidget::music_1_Clicked()
{
    music_1_Choose->setStyleSheet(BUTTON_STYLE_4);
    music_2_Choose->setStyleSheet(BUTTON_STYLE_3);
}
void ReadMeWidget::music_2_Clicked()
{
    music_2_Choose->setStyleSheet(BUTTON_STYLE_4);
    music_1_Choose->setStyleSheet(BUTTON_STYLE_3);
}
void ReadMeWidget::bullet_0_Clicked()
{
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_3);
    bulletChoose[0]->setStyleSheet(BUTTON_STYLE_4);
    bullet=0;
}
void ReadMeWidget::bullet_1_Clicked()
{
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_3);
    bulletChoose[1]->setStyleSheet(BUTTON_STYLE_4);
    bullet=1;
}
void ReadMeWidget::bullet_2_Clicked()
{
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_3);
    bulletChoose[2]->setStyleSheet(BUTTON_STYLE_4);
    bullet=2;
}
void ReadMeWidget::bullet_3_Clicked()
{
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_3);
    bulletChoose[3]->setStyleSheet(BUTTON_STYLE_4);
    bullet=3;
}
void ReadMeWidget::bullet_4_Clicked()
{
    bulletChoose[bullet]->setStyleSheet(BUTTON_STYLE_3);
    bulletChoose[4]->setStyleSheet(BUTTON_STYLE_4);
    bullet=4;
}

