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

    // Player creation
        Player player1("player1");
        Player player2("player2");

        // Country creation
        Country canada("canada",20);
        Country us("us",20);

        // add country to players
        player1.addCountry(canada.getNameCountry());
        player2.addCountry(us.getNameCountry());

        WarReferee warReferee = WarReferee::getInstance();

        // start automated war
        std::cout <<"Automatic dices rolls" << std::endl;
        std::cout <<"Current army in " << us.getNameCountry()<< ": " <<us.getArmies() << std::endl;
        std::cout <<"Current army in " << canada.getNameCountry()<< ": " <<canada.getArmies() << std::endl;
        std::cout <<"Current army in " << us.getNameCountry()<< ": " <<us.getArmies() << std::endl;
        warReferee.startWar(player1,canada,player2,us);
        std::cout <<"Current army in " << canada.getNameCountry() << " after the war : " <<canada.getArmies() << std::endl;
        std::cout <<"Current army in " << us.getNameCountry() << " after the war : " <<us.getArmies() << std::endl;

//        // reset soldiers in both countries
//        canada.setSoldiers(20);
//        us.setSoldiers(20);

//        warReferee.setPlayers(player1,player2);


//        // start manual war
//        std::cout <<"\n\n\nOnly 1 dice roll" << std::endl;
//        std::cout <<"Current army in " << canada.getName()<< ": " <<canada.getSoldiers() << std::endl;
//        std::cout <<"Current army in " << us.getName()<< ": " <<us.getSoldiers() << std::endl;
//        warReferee.calculateLosses(canada,us);
//        std::cout <<"Current army in " << canada.getName() << " after the war : "<<canada.getSoldiers() << std::endl;
//        std::cout <<"Current army in " << us.getName() << " after the war : "<<us.getSoldiers() << std::endl;


    return application.exec();
}
