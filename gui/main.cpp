#include <iostream>
#include <QApplication>

#include "librisk.h"
#include "main_window.h"
#include "country.h"
#include "continent.h"
#include "warreferee.h"
#include "player.h"
#include "playerview.h"
#include "risk_map.h"

using namespace std;

int main(int argc, char *argv[])
{
    librisk_init();

    // Player creation

    Player player1("player1");
    Player player2("player2");

    PlayerView pv;
    player1.registerObserver(&pv);


    RiskMap& map = RiskMap::getInstance();
    map.addCountry("Canada", "America", 20);
    map.addCountry("Us", "America", 20);
    map.getCountry("Canada")->setPlayer("player1");
    map.getCountry("Us")->setPlayer("player2");

    Country* canada = map.getCountry("Canada");
    Country* us = map.getCountry("Us");


    // add country to players
    player1.addCountry(canada->getName());
    player2.addCountry(us->getName());
    canada->setPlayer(player1.getName());
    us->setPlayer(player2.getName());
    WarReferee warReferee = WarReferee::getInstance();

    // start automated war
    std::cout <<"Automatic dices rolls" << std::endl;
    std::cout <<"Current army in " << canada->getName()<< ": " <<canada->getArmies() << std::endl;
    std::cout <<"Current army in " << us->getName()<< ": " <<us->getArmies() << std::endl;
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
