//#include <iostream>
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
#include "gamedriver.h"

using namespace std;
/**
 * @brief main the main for the gamedriver creates QApplication initializes a GameDriver singleton object
 * and opens the window of the gui.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	GameDriver* driver = GameDriver::getInstance();
	driver->showSplashScreen();
  return application.exec();
}
