#include "gamedriver1.h"
#include "risk_map.h"
#include "player.h"
#include <set>
#include <string>
using namespace std;

GameDriver1::GameDriver1(RiskMap *riskMap)
{
    this->riskMap = riskMap;
    for(auto const &ent1: riskMap->getPlayers()){
        const Player& p = ent1.second;
        Player *player = riskMap->getPlayer(p.getName());
        calculateReinforcementArmies(player);

    }

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


}

void GameDriver1::calculateReinforcementArmies(Player *p)
{

    set<string> continents =p->getContinentsOwned();
    set<string>::iterator itContinents = continents.begin();
    int reinforcementArmies=0;
    reinforcementArmies = p->getCountriesOwned().size()/3;
    while(itContinents!= continents.end()){
        reinforcementArmies += riskMap->getContinent(*itContinents)->getReinforcementBonus();
    }
    p->setReinforcements(reinforcementArmies);
}

