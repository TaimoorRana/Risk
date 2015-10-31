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

int main(int argc, char *argv[])
{
//    QApplication application(argc, argv);
//    return application.exec();

    using namespace std;
    QDate d1(2007, 10,2), d2(QDate::currentDate());
    int days;
    cout<<"I came to Canada on "<<d1.toString("MMMM d yyyy").toStdString()<<"\nToday's date is "<<d2.toString("MMMM d yyyy").toStdString()<<endl;
    days = d1.daysTo(d2);
    cout<<"There are "<<days<<" days between "<<d1.toString("dd MMM yyyy").toStdString()<<" and "<<d2.toString(Qt::ISODate).toStdString()<<endl;
    cout<<"Hellow"<<endl;
    return 0;
}
