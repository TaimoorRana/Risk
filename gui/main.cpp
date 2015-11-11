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

using namespace std;
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    QPixmap splashImg = QPixmap("/Users/taimoorrana/Desktop/Risk/gui/risk1.png").scaled(600, 300);
    splash->setPixmap(splashImg);
    splash->show();
    RiskMap map;
	Player player1("Taimoor");
    Player player2("Adrianna");
	Player player3("Elias");
	player1.setTotalArmy(500);
    map.addPlayer(player1);
    map.addPlayer(player2);
	map.addPlayer(player3);
	map.addPlayer(Player("stewart"));
	QTimer::singleShot(2500,splash,SLOT(close()));

    MainScreen w(&map,0);

	if(w.setupPlayers() == false)
	{
		application.exit();
		return -1;
	}

	QTimer::singleShot(2500,&w,SLOT(show()));
    w.show();

    return application.exec();
}
