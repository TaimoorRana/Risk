
#ifndef GAMEDRIVER_H

#define GAMEDRIVER_H

#include "fortify_dialog.h"

#include "risk_map.h"

#include "player.h"

#include "map_scene.h"

#include "mainscreen.h"
#include "game_modes.h"

#include <QSplashScreen>

#include <QPixmap>

#include <string>

#include <set>

#include <QTimer>
#include <vector>



using namespace std;

/**
 * @brief The GameDriver class
 * Handles the ordering of the game  the players turn the number of reinforcements
 * calculating the number of armies placed and allowed to place
 *
 *
 */

class GameDriver

{

public:




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
	 * @brief calculateReinforcementArmies calculates the reinforcements for the player using the continents and countries
	 * that the player owns.
	 * @param p the player pointer
	 *
	 */

	void calculateReinforcementArmies(Player *p);

	bool allArmiesPlaced; /**< checks whether all armies have been placed */

	/**
	 * @brief placeArmies sets the number of armies to place.
	 * @param i number of armies to place
	 *
	 */

	void placeArmies(int i);
	/**
	 * @brief setNumberOfPlayers sets the number of players
	 * @param numberOfPlayers game number of players
	 */

	void setNumberOfPlayers(int numberOfPlayers);

	//void setMode(Mode m);
	/**
	 * @brief attackPhase
	 */

	void attackPhase();
	/**
	 * @brief implements reinforcePhase
	 */

	void reinforcePhase();
	/**
	 * @brief implements fortificationPhase
	 */

	void fortificationPhase();
	/**
	 * @brief implements endTurn
	 */

	void endTurn();
	/**
	 * @brief showSplashScreen the splash screen on game start
	 */

	void showSplashScreen();
	/**
	 * @brief addPlayer adds a player in string format
	 * @param name
	 */

	void addPlayer(std::string name);
	/**
	 * @brief getInstance gets the singleton instance of the gamedriver
	 * @return
	 */

	static GameDriver* getInstance();



private:

	GameDriver();

	MapScene* mapScene;

	RiskMap* riskMap;

	MainScreen* mainWindow;

	//FortifyDialog fortificationDialog;

	int numberOfPlayers;



	bool gameBegun;

	bool canFortify;


};



#endif // GAMEDRIVER1_H

