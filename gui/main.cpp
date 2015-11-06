#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QTextStream>
#include <QSplashScreen>
#include <QTimer>

//#include "main_window.h"
#include "risk_map.h"
#include "mainscreen.h"
#include "playernamedialog.h"

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    QPixmap splashImg = QPixmap("/Users/taimoorrana/Desktop/Risk/gui/risk1.png").scaled(600, 300);
    splash->setPixmap(splashImg);
    splash->show();
    RiskMap map;
    Player player1("taimoor");
    Player player2("Adrianna");
    map.addPlayer(player1);
    map.addPlayer(player2);
    PlayerNameDialog dialog;

    MainScreen w(&map,0);


    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    QTimer::singleShot(2600,&dialog,SLOT(show()));


    return application.exec();

}
