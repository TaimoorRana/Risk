#include "gamedriver1.h"
using namespace std;

GameDriver1::GameDriver1(RiskMap *riskMap)
{
	MainScreen* mainWindow = new MainScreen(riskMap,0);
	this->riskMap = riskMap;
	mapScene = new MapScene(riskMap, mainWindow);
	QSplashScreen *splash = new QSplashScreen;
	QPixmap splashImg = QPixmap("/Users/taimoorrana/Desktop/Risk/gui/risk1.png").scaled(600, 300);
	splash->setPixmap(splashImg);
	QTimer::singleShot(2500,splash,SLOT(close()));

//    for(auto const &ent1: riskMap->getPlayers()){
//        const Player& p = ent1.second;
//        Player *player = riskMap->getPlayer(p.getName());
//        calculateReinforcementArmies(player);
//    }

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

