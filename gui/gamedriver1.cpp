

#include "gamedriver1.h"

using namespace std;

void GameDriver1::attackPhase(){}

void GameDriver1::reinforcePhase()

{
	currentMode = reinforceMode;
}



void GameDriver1::fortificationPhase()

{

	canFortify = true;
}



GameDriver1* GameDriver1::getInstance()
{
	static GameDriver1* instance = nullptr;

	if(instance == nullptr){
		instance = new GameDriver1();
	}
	return instance;
}



void GameDriver1::showSplashScreen()

{

	QSplashScreen *splash = new QSplashScreen;

	QPixmap splashImg = QPixmap("/Users/taimoorrana/Desktop/Risk/gui/risk1.png").scaled(600, 300);

	splash->setPixmap(splashImg);
	//splash->show();
	//QTimer::singleShot(2500,splash,SLOT(close()));

	delete splash;

	mainWindow->setupPlayers();
	mainWindow->show();
}



void GameDriver1::addPlayer(string name)

{

	Player* player = new Player(name);

	riskMap->addPlayer(*player);

}





GameDriver1::GameDriver1(){

	this->riskMap = new RiskMap;

	this->mainWindow = new MainScreen(riskMap,0);

	this->mapScene = new MapScene(riskMap, mainWindow);

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



