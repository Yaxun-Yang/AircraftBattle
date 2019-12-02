//
#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>

#include "global.h"
#include "themeWidget.h"
#include "battleWidget.h"
#include "newGameWidget.h"
#include "gameBoardWidget.h"
#include "gameOverWidget.h"
#include "readMeWidget.h"

class MainMenuWidget:public QWidget
{
    Q_OBJECT
private:

    QPushButton *continueTheGame;
    QPushButton *startANewGame;
    QPushButton *gameBoard;
    QPushButton *readMe;
    QPushButton *quitTheGame;

    QVBoxLayout* layout;
    //页面创造
    ThemeWidget *themeWidget;
    NewGameWidget *newGameWidget;
    BattleWidget *battleWidget;
    GameBoardWidget *gameBoardWidget;
    ReadMeWidget *readMeWidget;
    GameOverWidget *gameOverWidget;

    //音乐
    QMediaPlayer* player;
    QMediaPlaylist* playerList;

    //是否展现继续游戏按钮
    bool couldContinue;

    //偏好选择记录
    bool direction;
    bool music;
    int bullet;

private:
    void themeWidgetShow();

public:
    MainMenuWidget(QWidget * parent = 0 );
    ~MainMenuWidget();
public slots:
    //主菜单页面按钮的槽函数
    void continueTheGameCliked();
    void startANewGameCliked();
    void gameBoardCliked();
    void readMeClicked();
    void quitTheGameCliked();
    //新游戏页面按钮的槽函数
    void newGameWidgetMainMenuButtonCliked();
    void level_1_Cliked();
    void level_2_Cliked();
    void level_3_Cliked();
    void level_4_Cliked();
    void level_5_Cliked();
    //战斗页面按钮的槽函数
    void battleWidgetMainMenuButtonClicked();
    void newGameOver();
    //排行榜页面的槽函数
    void gameBoardWidgetMainMenuButtonClicked();
    //游戏结束页面槽函数
    void gameOverWidgetButtonClicked();
    //readMe页面槽函数
    void readMeWidgetMainMenuButtonClicked();
    void direction_1_Clicked();
    void direction_2_Clicked();
    void music_1_Clicked();
    void music_2_Clicked();
    void bullet_0_Clicked();
    void bullet_1_Clicked();
    void bullet_2_Clicked();
    void bullet_3_Clicked();
    void bullet_4_Clicked();
};

#endif // MAINMENUWIDGET_H
