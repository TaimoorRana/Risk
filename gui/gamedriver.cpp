#include "gamedriver.h"

using namespace std;

GameDriver* GameDriver::getInstance()
{
	static GameDriver* instance = nullptr;

    if(instance == nullptr){
		instance = new GameDriver();
    }
	return instance;
}

void GameDriver::attackPhase(){}

void GameDriver::reinforcePhase()
{
}

void GameDriver::fortificationPhase()

{

	canFortify = true;

	// click on country to add to set
    // click again to remove
    // if array is full pop up the fortification dialog
    // display names of selected countries
   

    //fortificationDialog = fortificationDialog(c1);
    
    
}



void GameDriver::showSplashScreen()

{
	QSplashScreen *splash = new QSplashScreen;

	QPixmap splashImg = QPixmap("../../../assets/risk1.png").scaled(600, 300);

	splash->setPixmap(splashImg);
	splash->show();
	QTimer::singleShot(2500,splash,SLOT(close()));

	delete splash;

	mainWindow->setupPlayers();
	mainWindow->show();

}



void GameDriver::addPlayer(string name)
{
	Player* player = new Player(name);
	riskMap->addPlayer(*player);
}

GameDriver::GameDriver(){

	this->riskMap = new RiskMap;
	this->mainWindow = new MainScreen(riskMap,0);
	this->mapScene = new MapScene(riskMap, mainWindow);
}



void GameDriver::calculateReinforcementArmies(Player *p)

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



