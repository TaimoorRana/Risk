

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

//    set<string> continents =p->getContinentsOwned();
//    set<string>::iterator itContinents = continents.begin();
//    int reinforcementArmies=0;
//    reinforcementArmies = p->getCountriesOwned().size()/3;
//    while(itContinents!= continents.end()){
//        reinforcementArmies += riskMap->getContinent(*itContinents)->getReinforcementBonus();
//    }
//    p->setReinforcements(reinforcementArmies);

}



