#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H

#include "global.h"
#include "themeWidget.h"

#include <QWidget>


class GameOverWidget : public QWidget
{
    Q_OBJECT
private:

    ThemeWidget* themeWidget;

    int credit;
    int level;
    QPushButton* playerButton;
    QPushButton* touristsButton;


    QLabel *IconShow;
    QLabel *creditShow;
    QLabel *modeShow;

    QPushButton* submitButton;
    QPushButton* cancelButton;
    QLabel *userName;
    QLineEdit *lineEdit;

    QMediaPlayer* player;
    QMediaPlaylist* playerList;

public:
     GameOverWidget(bool music,QWidget* mainMenu, int credit ,int level,QWidget *parent = 0);

signals:
    void over();

public slots:
    void playerButtonClicked();
    void submitButtonClicked();
    void cancelButtonClicked();
    void mediaPlayerClose();

};

#endif // GAMEOVERWIDGET_H
