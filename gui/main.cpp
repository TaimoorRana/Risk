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

#include "risk.h"
#include "country.h"
#include "dices.h"
#include "continent.h"
#include "warreferee.h"
#include "player.h"
#include "playerview.h"
#include "risk_map.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("gui/risk1.jpg"));
    splash->show();
    MainWindow w;
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    return application.exec();
}
