#include <iostream>
#include <QApplication>

#include "librisk.h"
#include "main_window.h"
#include "country.h"
#include "continent.h"
#include "warreferee.h"
#include "player.h"
#include "risk_map.h"

using namespace std;

int main(int argc, char *argv[])
{
    librisk_init();

    QApplication application(argc, argv);

    // Player creation
    Player player1("player1");
    Player player2("player2");

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
    warReferee.startWar(player1,*canada,player2,*us);
    std::cout <<"Current army in " << canada->getName() << " after the war : " <<canada->getArmies() << std::endl;
    std::cout <<"Current army in " << us->getName() << " after the war : " <<us->getArmies() << std::endl;

    // reset soldiers in both countries
    canada->setArmies(20);
    us->setArmies(20);
    us->setPlayer(player2.getName());

    // warReferee = WarReferee::getInstance();
    // // start manual war
    // std::cout <<"\n\n\n\nAutomatic dices rolls" << std::endl;
    // std::cout <<"Current army in " << canada.getName()<< ": " <<canada.getArmies() << std::endl;
    // std::cout <<"Current army in " << us.getName()<< ": " <<us.getArmies() << std::endl;
    // warReferee.startWar(player1,canada,player2,us);
    // std::cout <<"Current army in " << canada.getName() << " after the war : " <<canada.getArmies() << std::endl;
    // std::cout <<"Current army in " << us.getName() << " after the war : " <<us.getArmies() << std::endl;

    MainWindow* mw = new MainWindow();
    mw->show();

    return application.exec();
}
