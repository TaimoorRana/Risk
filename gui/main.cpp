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

#include "risk_map.h"
#include "mainscreen.h"
#include "playernamedialog.h"
#include "country_name_dialog.h"
#include "gamedriver1.h"

using namespace std;
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

	GameDriver1* driver = GameDriver1::getInstance();
	driver->addPlayer("taimoor");
	driver->addPlayer("Elias");
	driver->showSplashScreen();




    return application.exec();
}
