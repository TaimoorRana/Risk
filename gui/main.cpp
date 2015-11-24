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
//	GameDriver* driver = GameDriver::getInstance();
	showSplashScreen();

	RiskMap* riskMap = new RiskMap();
	MainScreen* mainScreen = new MainScreen(riskMap, 0);
//	MapScene* mapScene = new MapScene(riskMap, mainScreen);

	mainScreen->setupPlayers();
	mainScreen->show();

  return application.exec();
}
