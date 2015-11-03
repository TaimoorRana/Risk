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

	return application.exec();
}
