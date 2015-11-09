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
#include "risk_map.h"
#include "country_name_dialog.h"

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);

	RiskMap map = RiskMap();
	MainWindow* mw = new MainWindow(&map);

	mw->show();

    map.attachObserver(mw);

	return application.exec();
}
