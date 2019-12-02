#include "mainMenuWidget.h"

MainMenuWidget::MainMenuWidget(QWidget * parent):QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(WIDTH,HEIGHT);
    themeWidget=new ThemeWidget(this);
    couldContinue=false;
    newGameWidget=NULL;
    battleWidget=NULL;

    //偏好初始化

    direction=true;
    music=true;
    bullet=0;

    //音乐设置
    playerList = new QMediaPlaylist;
    playerList->setCurrentIndex(1);
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playerList->addMedia(QUrl::fromLocalFile("../sound/global.mp3"));
    player=new QMediaPlayer;
    player->setPlaylist(playerList);
    player->play();

    //数据库相关准备
    if (!Global::createConnection())
    {
        exit(128);
    }
    QSqlQuery query(Global::db);
    query.exec(QString("create table player ("
                       "id integer primary key autoincrement, "
                       "userName text not null ,"
                       "numberOfGame integer not null,"
                       "totCredit integer not null,"
                       "averageCredit double not null )"));

    //开始新游戏按钮的设置
    startANewGame= new QPushButton("Start A New Game",this);
    startANewGame->setIcon(QIcon(":/myAircraft.png"));
    startANewGame->setStyleSheet(BUTTON_STYLE_2);
    startANewGame->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(startANewGame,SIGNAL(clicked(bool)),this,SLOT(startANewGameCliked()));
    //排行榜按钮的设置
    gameBoard=new QPushButton("   Game Board   ",this);
    gameBoard->setIcon(QIcon(":/gameBoard.png"));
    gameBoard->setStyleSheet(BUTTON_STYLE_2);
    gameBoard->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(gameBoard,SIGNAL(clicked(bool)),this,SLOT(gameBoardCliked()));
    //Read Me 按钮
    readMe=new QPushButton("    Read Me    ",this);
    readMe->setIcon(QIcon(":/readMe.png"));
    readMe->setStyleSheet(BUTTON_STYLE_2);
    readMe->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(readMe,SIGNAL(clicked(bool)),this,SLOT(readMeClicked()));
    //退出游戏按钮的设置
    quitTheGame= new QPushButton("  Quit The Game  ",this);
    quitTheGame->setIcon(QIcon(":/otherAircraft.png"));
    quitTheGame->setStyleSheet(BUTTON_STYLE_2);
    quitTheGame->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
    connect(quitTheGame,SIGNAL(clicked(bool)),this,SLOT(quitTheGameCliked()));
    //垂直布局器的设置
    layout=new QVBoxLayout;
    layout->addWidget(startANewGame);
    layout->addWidget(gameBoard);
    layout->addWidget(readMe);
    layout->addWidget(quitTheGame);
    layout->setSpacing(3);
    layout->setContentsMargins(THEME_WIDGET_WIDTH,10,20,10);
    this->setLayout(layout);


}
 MainMenuWidget::~MainMenuWidget()
{
     themeWidget->close();
    themeWidget->~ThemeWidget();
}

void MainMenuWidget::continueTheGameCliked()
{
    battleWidget->show();
    player->pause();
    this->hide();
}

void MainMenuWidget::startANewGameCliked()
{
    newGameWidget= new NewGameWidget(this);
    newGameWidget->show();
    this->hide();

}

void MainMenuWidget::gameBoardCliked()
{
    gameBoardWidget=new GameBoardWidget(this);
    gameBoardWidget->show();
    this->hide();
}

void MainMenuWidget::readMeClicked()
{
    readMeWidget=new ReadMeWidget(this,direction,music,bullet);
    readMeWidget->show();
    this->hide();
}

void MainMenuWidget::quitTheGameCliked()
{
    player->stop();
    this->close();
}
//展示主题动画效果
void MainMenuWidget::themeWidgetShow()
{
    themeWidget->close();
    themeWidget=new ThemeWidget(this);
    this->show();
    themeWidget->show();
}
//战斗页面链接槽函数
void MainMenuWidget::battleWidgetMainMenuButtonClicked()
{
    battleWidget->hide();
    player->play();
    //继续游戏按钮的设置
    if(!couldContinue)
    {
       couldContinue=true;
       continueTheGame= new QPushButton("Continue The Game",this);
       continueTheGame->setIcon(QIcon(":/continue.png"));
       continueTheGame->setStyleSheet(BUTTON_STYLE_2);
       continueTheGame->setIconSize(QSize(BUTTON_ICON_SIZE_2,BUTTON_ICON_SIZE_2));
       connect(continueTheGame,SIGNAL(clicked(bool)),this,SLOT(continueTheGameCliked()));
       layout->addWidget(continueTheGame);
       layout->addWidget(startANewGame);
       layout->addWidget(gameBoard);
       layout->addWidget(readMe);
       layout->addWidget(quitTheGame);
    }
    themeWidgetShow();
}

void MainMenuWidget::newGameOver()
//玩家飞机死亡游戏结束
{
    gameOverWidget=new GameOverWidget(music,this,battleWidget->getCredit(),battleWidget->getMode());
    gameOverWidget->show();
    battleWidget->close();
    battleWidget=NULL;
    if(couldContinue)
    {
        couldContinue=false;
        continueTheGame->~QPushButton();
        continueTheGame=NULL;
    }
}

void MainMenuWidget::gameOverWidgetButtonClicked()
//游戏结束页面结束按钮被点击
{
    if(music)
    player->play();
    gameOverWidget->close();
    themeWidgetShow();
}

void MainMenuWidget::gameBoardWidgetMainMenuButtonClicked()
//排行榜页面链接槽函数
{
    gameBoardWidget->close();
    gameBoardWidget=NULL;
    themeWidgetShow();
}

void MainMenuWidget::newGameWidgetMainMenuButtonCliked()
//游戏模式选择页面链接槽函数
{
    newGameWidget->close();
    newGameWidget=NULL;
    themeWidgetShow();
}

void MainMenuWidget::level_1_Cliked()
{
    if(couldContinue)
    {
        battleWidget->close();
    }
    player->pause();
    newGameWidget->close();
    newGameWidget=NULL;
    battleWidget=new BattleWidget(direction,music,bullet,1,this);
    battleWidget->show();
    this->hide();
}
void MainMenuWidget::level_2_Cliked()
{
    if(couldContinue)
    {
        battleWidget->close();
    }
    player->pause();
    newGameWidget->close();
    newGameWidget=NULL;
    battleWidget=new BattleWidget(direction,music,bullet,2,this);
    battleWidget->show();
    this->hide();
}
void MainMenuWidget::level_3_Cliked()
{
    if(couldContinue)
    {
        battleWidget->close();
    }
    player->pause();
    newGameWidget->close();
    newGameWidget=NULL;
    battleWidget=new BattleWidget(direction,music,bullet,3,this);
    battleWidget->show();
    this->hide();
}
void MainMenuWidget::level_4_Cliked()
{
    if(couldContinue)
    {
        battleWidget->close();
    }
    player->pause();
    newGameWidget->close();
    newGameWidget=NULL;
    battleWidget=new BattleWidget(direction,music,bullet,4,this);
    battleWidget->show();
    this->hide();
}
void MainMenuWidget::level_5_Cliked()
{
    if(couldContinue)
    {
        battleWidget->close();
    }
    player->pause();
    newGameWidget->close();
    newGameWidget=NULL;
    battleWidget=new BattleWidget(direction,music,bullet,5,this);
    battleWidget->show();
    this->hide();
}


//read me 页面链接槽函数
void MainMenuWidget::readMeWidgetMainMenuButtonClicked()
//主菜单
{
    readMeWidget->close();
    readMeWidget=NULL;
    themeWidgetShow();
}
//方向选择
void MainMenuWidget::direction_1_Clicked()
{
    direction = true;
}
void MainMenuWidget::direction_2_Clicked()
{
    direction =false;
}
void MainMenuWidget:: music_1_Clicked()
{
    music=true;
    player->play();
}
void MainMenuWidget:: music_2_Clicked()
{
    music=false;
    player->stop();
}
void MainMenuWidget::bullet_0_Clicked()
{
    bullet=0;
}
void MainMenuWidget::bullet_1_Clicked()
{
    bullet=1;
}
void MainMenuWidget::bullet_2_Clicked()
{
    bullet=2;
}
void MainMenuWidget::bullet_3_Clicked()
{
    bullet=3;
}
void MainMenuWidget::bullet_4_Clicked()
{
    bullet=4;
}
