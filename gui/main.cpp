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
#include "dicesreferee.h"

namespace yolo {
int x =1;
}


int main(int argc, char *argv[])
{

	QApplication application(argc, argv);
//    Dices *dices = new Dices(3);
//    std::vector<int> *re = dices->roll();

//    for(int x = 0; x < re->size(); x++){
//        std::cout << re->at(x) << std::endl;
//    }
    Player *taimoor = new Player("taimoor");
    Player *rana = new Player("Rana");
    Continent *america = new Continent("America",5);
    Country *canada = new Country("Canada",america,3,3);
    Country *us = new Country("Us",america,3,3);

    taimoor->addCountry(canada);
    rana->addCountry(us);
    std::cout << "current army in " << canada->getName()<<": " << canada->getSoldiers() << std::endl;
    std::cout << "current army in " << us->getName()<<": " << us->getSoldiers() << std::endl;
    DicesReferee *dicesreferee = new DicesReferee();
    dicesreferee->startWar(canada,3,us,2);
    std::cout << "Canada is attaking US" << std::endl;
    std::cout << "current army in " << canada->getName()<<" after war: " << canada->getSoldiers() << std::endl;
    std::cout << "current army in " << us->getName()<<" after war: "<< us->getSoldiers() << std::endl;
	return application.exec();
}
