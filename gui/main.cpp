#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QTextStream>
#include "player.h"
#include "country.h"
#include "continent.h"

#include "risk_map.h"
#include "main_window.h"

using namespace std;
int main(int argc, char *argv[]) {



    RiskMap *map = new RiskMap();
    map->addCountry("Ontaro","America",1);
    map->addCountry("Quebec","America",1);
    map->addCountry("New Brunswick","America",1);
    map->addCountry("New York","America",1);
    map->addNeighbour("Ontario","Quebec");
    map->addNeighbour("Ontario","NewYork");
    map->addNeighbour("Quebec","NewBrunswick");
    map->addNeighbour("Quebec","NewYork");
    Country *ontario = map->getCountry("Ontario");
    Country *quebec = map->getCountry("Quebec");
    Country *newBrunswick = map->getCountry("New Brunswick");
    Country *newYork = map->getCountry("NewYork");





    Player stewart = Player("Stewart");
    Player adrianna = Player("Adrianna");
    Player elliott = Player("Elliott");

    map->addPlayer(stewart);
    map->addPlayer(adrianna);

    map->addPlayer(elliott);

    cout <<"gello";
}
