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

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);

	RiskMap map = RiskMap();
	MainWindow* mw = new MainWindow(&map);

//    ClickableMap cm;
//    mw->addAction(cm);

	mw->show();

    map.attachObserver(mw);


	return application.exec();
}
