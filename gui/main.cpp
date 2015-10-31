#include <iostream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QTextStream>

#include "risk.h"
#include "country.h"
#include "dices.h"
#include "continent.h"
#include "warreferee.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    return application.exec();
}
