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

#include "main_window.h"
#include "risk_map.h"

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("gui/risk1.jpg"));
    splash->show();
    MainWindow w;
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    return application.exec();

}
