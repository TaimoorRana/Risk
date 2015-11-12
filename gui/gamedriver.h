
#ifndef GAMEDRIVER_H

#define GAMEDRIVER_H

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

/**
 * @brief The GameDriver1 class
 * Handles the ordering of the game  the players turn the number of reinforcements
 * calculating the number of armies placed and allowed to place
 *
 *
 */

class GameDriver

{

public:


	//player ordering

	//need using namespace std.

	//player needs to know it his turn

	//GameDriver(RiskMap *riskMap);



	~GameDriver();

	/**
	 * @brief setPlayerName sets the name of the current players turn
	 * @param s the current players turn
	  */
	void setPlayerName(string s);
	/**
	 * @brief getPlayerName
	 * returns the name of the current players turn
	 * @return
	 *
	 */

	string getPlayerName();
	/**
	 * @brief calculateReinforcementArmies
	 * @param p the player pointer
	 * calculates the reinforcements for the player using the continents and countries
	 * that the player owns.
	 */

	void calculateReinforcementArmies(Player *p);

	bool allArmiesPlaced; /**< checks whether all armies have been placed */
	/**
	 * @brief placeArmies
	 * @param i number of armies to place
	 * sets the number of armies to place
	 */

	void placeArmies(int i);

	void setNumberOfPlayers(int numberOfPlayers);

	//void setMode(Mode m);

	void attackPhase();

	void reinforcePhase();

	void fortificationPhase();

	void endTurn();

	void showSplashScreen();

	void addPlayer(std::string name);

	static GameDriver* getInstance();



private:

	GameDriver();

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

