#include "gamedriver1.h"
#include "player.h"
#include <set>
#include <string>
using namespace std;

GameDriver1::GameDriver1(MapScene *aScene)
{
    this->scene = aScene;
//    for(auto const &ent1: riskMap->getPlayers()){
//        const Player& p = ent1.second;
//        Player *player = riskMap->getPlayer(p.getName());
//        calculateReinforcementArmies(player);
//}

}

void GameDriver1::attackPhase()
{

}

void GameDriver1::reinforcePhase()
{
    currentMode = reinforceMode;
}

void GameDriver1::fortificationPhase()
{
    canFortify = true;

    // click on country to add to set
    // click again to remove
    // if array is full pop up the fortification dialog
    // display names of selected countries
    Country c1;
    c1.setName("A");
    Country c2;
    c2.setName("B");

    Country selectedCountries[2];
    selectedCountries[0]=c1;
    selectedCountries[1]=c2;

    // check for adjancency
    if (scene->getMap()->areCountriesAdjacent(c1.getName(), c2.getName()))
    {
        // pop-up the transfer window
        fortificationDialog.setOriginCountryName(QString::fromStdString(c1.getName()));
        fortificationDialog.setDestinationCountryName(QString::fromStdString(c2.getName()));

        fortificationDialog.show();
    } else
    {
        // pop-up the transfer window
        fortificationDialog.setOriginCountryName(QString::fromStdString("NAANANANNA"));
        fortificationDialog.setDestinationCountryName(QString::fromStdString("BOOOOOOO"));

        fortificationDialog.show();
        // pop-up a non adjacent window
    }
}

void GameDriver1::calculateReinforcementArmies(Player *p)
{

//    set<string> continents =p->getContinentsOwned();
//    set<string>::iterator itContinents = continents.begin();
//    int reinforcementArmies=0;
//    reinforcementArmies = p->getCountriesOwned().size()/3;
//    while(itContinents!= continents.end()){
//        reinforcementArmies += riskMap->getContinent(*itContinents)->getReinforcementBonus();
//    }
//    p->setReinforcements(reinforcementArmies);
}

