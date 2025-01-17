#-------------------------------------------------
#
# Project created by QtCreator 2019-07-09T19:23:03
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = AircraftBattle
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_FILE  += AircraftBattle.rc
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    battleWidget.cpp \
    aircraft.cpp \
    myAircraft.cpp \
    otherAircraft.cpp \
    bullet.cpp \
    myBullet.cpp \
    otherBullet.cpp \
    global.cpp \
    mainMenuWidget.cpp \
    newGameWidget.cpp \
    themeWidget.cpp \
    gameBoardWidget.cpp \
    gameOverWidget.cpp \
    readMeWidget.cpp

HEADERS  += \
    battleWidget.h \
    aircraft.h \
    myAircraft.h \
    otherAircraft.h \
    bullet.h \
    myBullet.h \
    otherBullet.h \
    global.h \
    mainMenuWidget.h \
    newGameWidget.h \
    themeWidget.h \
    gameBoardWidget.h \
    gameOverWidget.h \
    readMeWidget.h

DISTFILES +=

RESOURCES += \
    ../Images/images.qrc
