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
#include "player.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    Player player("taimoor");
    player.addCountry("canada");
    player.addCountry("us");
    player.addCountry("russia");
    vector<std::string> test = player.getCountryOwned();
    for(int x = 0; x < test.size(); x++){
        cout<< test[x] << endl;
    }
    player.removeCountry("canada");
    test = player.getCountryOwned();
    for(int x = 0; x < test.size(); x++){
        cout<< test[x] << endl;
    }

    return application.exec();
}
