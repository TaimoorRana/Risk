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
#include "playerview.h"
#include "risk_map.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Player creation

    Player player1("player1");
    Player player2("player2");

    PlayerView pv;
    player1.registerObserver(&pv);


    RiskMap& map = RiskMap::getInstance();
    map.addCountry("Canada", "America", 20);
    map.addCountry("Us", "America", 20);
    map.setPlayerOwner("Canada", "player1");
    map.setPlayerOwner("Us", "player2");

    Country* canada = map.getCountryObj("Canada");
    Country* us = map.getCountryObj("Us");


    // add country to players
    player1.addCountry(canada->getNameCountry());
    player2.addCountry(us->getNameCountry());
    canada->setPlayer(player1.getName());
    us->setPlayer(player2.getName());
    WarReferee warReferee = WarReferee::getInstance();

    // start automated war
    std::cout <<"Automatic dices rolls" << std::endl;
    std::cout <<"Current army in " << canada->getNameCountry()<< ": " <<canada->getArmies() << std::endl;
    std::cout <<"Current army in " << us->getNameCountry()<< ": " <<us->getArmies() << std::endl;
    std::string player1name = "taimoor";
    std::string player2name = "rana";
    int attackerArmy = 20;
    int defenderArmy = 20;
    warReferee.startWar(player1name,attackerArmy,player2name,defenderArmy);
    std::cout <<"Current army in " << warReferee.getAttackerPlayer() << " after the war : " << warReferee.getAttackerArmy() << std::endl;
    std::cout <<"Current army in " << warReferee.getDefenderPlayer() << " after the war : " << warReferee.getDefenderArmy() << std::endl;
    player1.notifyObserver();

    std::cout << pv.getNumberOfArmies() << "test";

    QApplication application(argc, argv);
    return application.exec();
}
