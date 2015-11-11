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


    RiskMap map;


    Player player1("taimoor");
    Player player2("Adrianna");
	Player player3("Elias");
	player1.setTotalArmy(500);
    map.addPlayer(player1);
    map.addPlayer(player2);
	map.addPlayer(player3);
	map.addPlayer(Player("stewart"));
    MainScreen w(&map,0);
    w.setupPlayers();
	QTimer::singleShot(2500,&w,SLOT(show()));
    w.show();

    return application.exec();
}
