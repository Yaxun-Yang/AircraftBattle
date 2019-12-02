#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include "global.h"

#include <QWidget>

#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QSqlError>

#define USER_NAME_WIDTH 150
#define NUMBER_OF_GAME_WIDTH 120
#define ID_WIDTH 50

class GameBoardWidget : public QWidget
{
    Q_OBJECT
private:
    int sortChosen;

    QPushButton* mainMenuButton;
    QPushButton* searchButton;
    QPushButton* showAllButton;
    QPushButton* deleteButton;
    QPushButton* deleteAllButton;

    QPushButton* sortButton[4];

    QLineEdit* lineEdit;

    QTableView* tableView;
    QSqlQueryModel* model;
private:
    void showSortChosen();
public:
     GameBoardWidget(QWidget * mainMenuWidget,QWidget *parent = 0);

public slots:
     void searchButtonClicked();
     void showAllButtonClicked();
     void deleteButtonClicked();
     void deleteAllButtonClicked();

     void totCreditSortClicked();
     void averageCreditSortClicked();
     void numberOfGameSortClicked();
     void idSortClicked();

};

#endif // GAMEBOARDWIDGET_H
