#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QTextStream>

#include "main_window.h"
#include "map.h"

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);

	Map map = Map();
	MainWindow* mw = new MainWindow(&map);
	mw->show();

	map.attachObserver(mw);

	map.parse("../../maps/World/World.map");

	Player stewart = Player("Stewart");
	Player adrianna = Player("Adrianna");
	Player taimoor = Player("Taimoor");
	Player elias = Player("Elias");
	Player elliott = Player("Elliott");

	map.addPlayer(&stewart);
	map.addPlayer(&adrianna);
	map.addPlayer(&taimoor);
	map.addPlayer(&elias);
	map.addPlayer(&elliott);

	return application.exec();
}
