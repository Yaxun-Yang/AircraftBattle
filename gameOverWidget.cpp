#include "gameOverWidget.h"

GameOverWidget::GameOverWidget(bool music,QWidget* mainMenu,
                    int credit, int level, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(WIDTH,HEIGHT);
    this->credit=credit;
    this->level=level;
    themeWidget=new ThemeWidget(this);

    //音乐设置
     playerList= new QMediaPlaylist;
     playerList->setCurrentIndex(1);
     playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
     playerList->addMedia(QUrl::fromLocalFile("../sound/myAircraftExplode.mp3"));
     player=new QMediaPlayer;
     player->setPlaylist(playerList);
     if(music)
     player->play();


    //玩家飞机图标
    QPixmap flyerPix(":/myAircraft.png");

    IconShow=new QLabel(this);
    IconShow->setGeometry(500,30,100,100);
    flyerPix.scaled(IconShow->size(),Qt::KeepAspectRatioByExpanding);
    IconShow->setPixmap(flyerPix);
    IconShow->setScaledContents(true);
    //游戏积分显示
    creditShow=new QLabel(this);
    creditShow->
        setText(QString("credit: ").append(QString::number(credit,10)));
    creditShow->setFont(QFont("FangSong",30,100));
    creditShow->setGeometry(420,160,260,80);
    //游戏模式显示
    modeShow=new QLabel(this);
    modeShow->setFont(QFont("FangSong",26,100));
    QString mode;
    switch(level)
    {
        case 1:
        mode="Patience Mode";
        modeShow->setFont(QFont("FangSong",20,100));
        break;
        case 2:mode="Easy Mode";break;
        case 3:mode="Normal Mode";break;
        case 4:mode="Hard Mode";break;
        case 5:mode="Crazy Mode";break;
    }
    mode=QString("Mode:").append(mode);
    modeShow->setText(mode);

    modeShow->setGeometry(400,240,300,80);

    //玩家按钮
    playerButton=new QPushButton(" I am a player ",this);
    playerButton->setGeometry(420,350,260,80);
    playerButton->setIcon(QIcon(":/user.png"));
    playerButton->setStyleSheet(BUTTON_STYLE_2);
    playerButton->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(playerButton,SIGNAL(clicked(bool)),this
            ,SLOT(playerButtonClicked()));
    //游客按钮
    touristsButton = new QPushButton("I am a tourist",this);
    touristsButton->setGeometry(420,450,260,80);
    touristsButton->setIcon(QIcon(":/user.png"));
    touristsButton->setStyleSheet(BUTTON_STYLE_2);
    touristsButton->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(touristsButton,SIGNAL(clicked(bool)),mainMenu
            ,SLOT(gameOverWidgetButtonClicked()));
    connect(touristsButton,SIGNAL(clicked(bool)),this
            ,SLOT(mediaPlayerClose()));
    //用户名输入提示
    userName=new QLabel(this);
    userName->hide();
    userName->setText(QString("user: "));
    userName->setGeometry(420,350,80,100);
    userName->setFont(QFont("FangSong",20,100));
    //输入框
    lineEdit=new QLineEdit(this);
    lineEdit->hide();
    lineEdit->setGeometry(500,380,180,40);
    lineEdit->setPlaceholderText(QString("Enter a user name"));
    lineEdit->setMaxLength(17);
    lineEdit->setFont(QFont("FangSong",14,50));
    //提交按钮
    submitButton = new QPushButton("Submit",this);
    submitButton->hide();
    submitButton->setGeometry(420,450,120,80);
    submitButton->setIcon(QIcon(":/submit.png"));
    submitButton->setStyleSheet(BUTTON_STYLE_3);
    submitButton->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(submitButton,SIGNAL(clicked(bool)),this
            ,SLOT(submitButtonClicked()));
    connect(submitButton,SIGNAL(clicked(bool)),this,SLOT(mediaPlayerClose()));
    //取消按钮
    cancelButton = new QPushButton("Cancel",this);
    cancelButton->hide();
    cancelButton->setGeometry(560,450,120,80);
    cancelButton->setIcon(QIcon(":/cancel.png"));
    cancelButton->setStyleSheet(BUTTON_STYLE_3);
    cancelButton->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(cancelButton,SIGNAL(clicked(bool)),this
            ,SLOT(cancelButtonClicked()));

    connect(this,SIGNAL(over()),mainMenu,SLOT(gameOverWidgetButtonClicked()));
}
void GameOverWidget::playerButtonClicked()
{
    playerButton->hide();
    touristsButton->hide();

    userName->show();
    lineEdit->show();
    submitButton->show();
    cancelButton->show();
}

void GameOverWidget::submitButtonClicked()
//在数据库中搜索用户名，已存在则更新数据不存在则创建并储存
{

    QString user=lineEdit->text();
    QSqlQuery query(Global::db);
    query.exec(QString("select count(*) from player where userName='%1';").arg(user));
    query.next();


    if(query.value(0).toInt())
    {
        query.exec(QString("select * from player where userName ='%1';").arg(user));
        int numberOfGame=0,totCredit=0;
        int averageCredit=0;
        while(query.next())
        {

            numberOfGame=query.value(2).toInt()+1;
            totCredit=query.value(3).toInt()+credit;
            averageCredit=totCredit/numberOfGame;
        }
        query.exec(QString("update player set numberOfGame = '%1'  where "
            "userName = '%2' ").arg(QString::number(numberOfGame,10),user));
        query.exec(QString("update player set totCredit = '%1'  where "
            "userName = '%2' ").arg(QString::number(totCredit,10),user));
        query.exec(QString("update player set averageCredit = '%1'  where "
            "userName = '%2' ").arg(QString::number(averageCredit,10),user));
    }
    else
    {
        query.exec(QString("insert into player (userName , numberOfGame ,"
                    "totCredit , averageCredit ) values ( '%1' , '1' ,'%2',"
    "'%3')").arg(user,QString::number(credit,10),QString::number(credit,10)));

    }
    emit over();
}

void GameOverWidget::cancelButtonClicked()
//恢复原来的页面
{
    userName->hide();
    submitButton->hide();
    cancelButton->hide();
    lineEdit->hide();

   playerButton->show();
   touristsButton->show();
}
void GameOverWidget::mediaPlayerClose()
{
    player->stop();
}
