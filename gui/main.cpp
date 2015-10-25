#include <iostream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

#include "risk.h"
#include "player.h"
#include "country.h"
#include "dices.h"
#include "continent.h"
#include "warreferee.h"

int main(int argc, char *argv[])
{

	QApplication application(argc, argv);
    Player taimoor("taimoor");
    Player rana("rana");
    Continent america("America", 10);
    Country canada("Canada", america,3,3);
    Country us("Us",america,3,4);
    taimoor.addCountry(canada);
    rana.addCountry(us);
    WarReferee warreferee;
    canada.adjustSoldiers(20);
    us.adjustSoldiers(20);
    std::cout << canada.getSoldiers() << "\n";
    std::cout << us.getSoldiers() << "\n";
    warreferee.startWar(taimoor,canada,rana,us);
    std::cout << canada.getSoldiers() << "\n";
    std::cout << us.getSoldiers() << "\n";
	return application.exec();
}
