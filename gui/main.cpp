#include <QApplication>
#include <QSplashScreen>
#include <QThread>

#include "game_driver.h"
#include "mainscreen.h"
#include "map_scene.h"

#include "risk_map.h"


void showSplashScreen() {
	QSplashScreen splash(QPixmap(":/splash.png").scaled(800, 346));
	splash.show();

	qApp->processEvents();
	QThread::msleep(1000);

	splash.close();
}

/**
 * @brief main the main for the gamedriver creates QApplication initializes a GameDriver singleton object
 * and opens the window of the gui.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	showSplashScreen();

	RiskMap* riskMap = new RiskMap();
	GameDriver* driver = GameDriver::getInstance();
	driver->setRiskMap(riskMap);
	MainScreen* mainScreen = new MainScreen(driver);

	mainScreen->setupPlayers();
	mainScreen->show();

  return application.exec();
}
