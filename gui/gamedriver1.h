
#ifndef GAMEDRIVER1_H

#define GAMEDRIVER1_H

#include "fortify_dialog.h"

#include "risk_map.h"

#include "player.h"

#include "map_scene.h"

#include "mainscreen.h"

#include <QSplashScreen>

#include <QPixmap>

#include <string>

#include <set>

#include <QTimer>

using namespace std;

class GameDriver1

{

public:


	//player ordering

	//need using namespace std.

	//player needs to know it his turn

	//GameDriver1(RiskMap *riskMap);

	~GameDriver1();

	enum Mode{reinforceMode,attackMode,moveMode, endOfTurnMode};

	Mode currentMode = reinforceMode;

	void setPlayerName(string s);

	string getPlayerName();

	void calculateReinforcementArmies(Player *p);

	bool allArmiesPlaced;

	void placeArmies(int i);

	void setNumberOfPlayers(int numberOfPlayers);

	//void setMode(Mode m);

	void attackPhase();

	void reinforcePhase();

	void fortificationPhase();

	void endTurn();

	void showSplashScreen();

	void addPlayer(std::string name);

	static GameDriver1* getInstance();



private:

	GameDriver1();

	MapScene* mapScene;

	RiskMap* riskMap;

	MainScreen* mainWindow;
    
    //FortifyDialog fortificationDialog;

	int numberOfPlayers;

	string currentPlayerName;

	bool gameBegun;

	bool canFortify;



};



#endif // GAMEDRIVER1_H

