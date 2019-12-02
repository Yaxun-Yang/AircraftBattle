//开始新游戏页面
#ifndef NEWGAMEWIDGET_H
#define NEWGAMEWIDGET_H

#include <QWidget>

#include "global.h"
#include "themeWidget.h"

class NewGameWidget : public QWidget
{
    Q_OBJECT
private:
    //模式选择按钮
    QPushButton * level1;
    QPushButton * level2;
    QPushButton * level3;
    QPushButton * level4;
    QPushButton * level5;
    //返回主菜单按钮
    QPushButton *mainMenuButton;
    //布局格式按钮
    QVBoxLayout *layout;

    ThemeWidget *themeWidget;
public:
    NewGameWidget(QWidget *mainMenuWidget,QWidget * parent = 0);
    ~NewGameWidget();


};

#endif // NEWGAMEWIDGET_H
