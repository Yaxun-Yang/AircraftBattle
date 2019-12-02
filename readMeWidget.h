#ifndef READMEWIDGET_H
#define READMEWIDGET_H

#include <QWidget>

#include "global.h"

class ReadMeWidget : public QWidget
{
    Q_OBJECT
private:
    int bullet;

    QPushButton* mainMenuButton;
    QPushButton* direction_1_Choose;
    QPushButton* direction_2_Choose;
    QPushButton* bulletChoose[5];
    QPushButton* music_1_Choose;
    QPushButton* music_2_Choose;

    QLabel* title;
    QLabel* subTitle;

    QLabel* text1;
    QLabel* text2;
    QLabel* text3;
    QLabel* text4;

    QLabel* picture1;
    QLabel* picture2;
    QLabel* picture3;

public:
     ReadMeWidget(QWidget* mainMenuWidget,bool direction,bool music,
                  int bullet, QWidget *parent = 0);

public slots:
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

#endif // READMEWIDGET_H
