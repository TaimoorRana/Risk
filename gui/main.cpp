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
#include "risk_map.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Player creation
        Player player1("player1");
        Player player2("player2");
    
        RiskMap map = RiskMap::getInstance();
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
        warReferee.startWar(player1,*canada,player2,*us);
        std::cout <<"Current army in " << canada->getNameCountry() << " after the war : " <<canada->getArmies() << std::endl;
        std::cout <<"Current army in " << us->getNameCountry() << " after the war : " <<us->getArmies() << std::endl;

        // reset soldiers in both countries
        canada->setArmies(20);
        us->setArmies(20);
        us->setPlayer(player2.getName());
//
//        warReferee = WarReferee::getInstance();
//        // start manual war
//        std::cout <<"\n\n\n\nAutomatic dices rolls" << std::endl;
//        std::cout <<"Current army in " << canada.getNameCountry()<< ": " <<canada.getArmies() << std::endl;
//        std::cout <<"Current army in " << us.getNameCountry()<< ": " <<us.getArmies() << std::endl;
//        warReferee.startWar(player1,canada,player2,us);
//        std::cout <<"Current army in " << canada.getNameCountry() << " after the war : " <<canada.getArmies() << std::endl;
//        std::cout <<"Current army in " << us.getNameCountry() << " after the war : " <<us.getArmies() << std::endl;
//    


    return application.exec();
}
