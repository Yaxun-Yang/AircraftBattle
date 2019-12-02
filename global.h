//全局基本类
#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdlib>

#include <QWidget>
#include <QString>
#include <QApplication>
#include <QKeyEvent>
#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QImage>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QtCore>
#include <QLabel>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//游戏页面固定大小
#define WIDTH 700
#define HEIGHT 540
//飞机大小
#define OTHER_AIRCRAFT_SIZE 30
#define MY_AIRCRAFT_SIZE 50
#define BIG_OTHER_AIRCRAFT_SIZE 80
//子弹大小
#define MY_BULLET_WIDTH 7
#define MY_BULLET_HEIGHT 12
#define OTHER_BULLET_WIDTH 5
#define OTHER_BULLET_HEIGHT 8
//基准时间
#define ONE_SECOND 1000
//飞机爆炸云停留时间
#define EXPLODE_TIME 1000
//战斗页面刷新的时间
#define UPDATE_TIME 50
//子弹速度
#define BULLET_SPEED 25
//主题页面宽度
#define THEME_WIDGET_WIDTH 400
//QPushButton Icon 图标大小
#define BUTTON_ICON_SIZE_1 36
#define BUTTON_ICON_SIZE_2 36
#define BUTTON_ICON_SIZE_3 20
// QPushButton 按钮样式表
#define BUTTON_STYLE_1 "QPushButton{ background-color:lightGray;font-family:FangSong;\
font-size:36px;border-radius:10px;border:1px} QPushButton:hover{ border-style:outset;}"
#define BUTTON_STYLE_2 "QPushButton{ background-color:lightGray;font-family:FangSong;\
font-size:24px;border-radius:10px;border:1px} QPushButton:hover{ border-style:outset;}"
#define BUTTON_STYLE_3 "QPushButton{ background-color:lightGray;font-family:FangSong;\
font-size:20px;border-radius:10px;border:1px} QPushButton:hover{ border-style:outset;}"
#define BUTTON_STYLE_4 "QPushButton{ background-color:Gray;font-family:FangSong;\
font-size:20px;border-radius:10px;border:1px} QPushButton:hover{ border-style:outset;}"


class Global
{
public:
   static QSqlDatabase db ;
   static bool createConnection();

};

#endif // GLOBAL_H
