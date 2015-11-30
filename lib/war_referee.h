#ifndef DICESREFEREE
#define DICESREFEREE
#include <iostream>
#include <string>

#include "country.h"
#include "player.h"

class WarReferee{

//use singleton pattern
private:
	WarReferee();
	static const int MAX_DICES = 3; ///< Max dices the WarReferee can use
	Player* attackerPlayer; ///< The Attacking player
	Player* defenderPlayer; ///< The Defending player

	// players armies
	int attackerArmy; ///< Attacking player's army
	int defenderArmy; ///< Defending player's army

	int defenderDices; ///< Dices used by the defender
	int attackerDices; ///< Dices used by the attacker

	Country* attackerCountry;
	Country* defenderCountry;

	/**
	 * @brief calculateLossesHelper
	 * This method rolls dices for the attacker and defender. It calculates army lost for each and assignes it to their respective army
	 */
	void calculateLossesHelper();

public:

	/**
	 * @brief getInstance Singleton pattern
	 * @return  WarReferee Object
	 */
	static WarReferee& getInstance();

	/*
	 Player related methods
	 @params string: player name
	 */

	/**
	 * @brief setAttackerPlayer
	 * @param player
	 */
	void setAttackerPlayer(Player* player);

	/**
	 * @brief setDefenderPlayer
	 * @param player
	 */
	void setDefenderPlayer(Player* player);
	/**
	 * @brief setBothPlayers
	 * @param attackerName
	 * @param defenderName
	 */
	void setBothPlayers(Player* attacker , Player* defender);

	/**
	 * @brief getAttackerPlayer
	 * @return attacker player
	 */
	Player* getAttackerPlayer();

	/**
	 * @brief getDefenderPlayer
	 * @return defender player
	 */
	Player* getDefenderPlayer();

	/*
	 Player Army related methods
	 @params int&: number of army
	 */
	/**
	 * @brief setDefenderArmy
	 * @param army
	 */
	void setDefenderArmy(int& army);

	/**
	 * @brief setAttackerArmy
	 * @param army
	 */
	void setAttackerArmy(int& army);

	/**
	 * @brief setBothArmies
	 * @param attackerArmy
	 * @param defenderArmy
	 */
	void setBothArmies(int &attackerArmy, int &defenderArmy);

	/**
	 * @brief getAttackerArmy
	 * @return attacker's army
	 */
	int getAttackerArmy();

	/**
	 * @brief getDefenderArmy
	 * @return defender's army
	 */
	int getDefenderArmy();

	/**
	 * @brief calculateLosses Roll dices for both players and calculate Losses occured to each army - dices are assigned depending on the army size
	 */
	void calculateLosses();

	/**
	 * @brief calculateLosses Roll dices for both players and calculate Losses occured to each army - dices amount is given by the user
	 * @param attackerDices attacker Dices amount
	 * @param defenderDices defender Dices amount
	 */
	void calculateLosses(int& attackerDices , int& defenderDices );

	/**
	 * @brief startWar Starts war between both players
	 * @param attackerCountry
	 * @param attackerArmy
	 * @param defenderCountry
	 * @param defenderArmy
	 */
	void startWar(Country* attackerCountry,Country* defenderCountry,Player* attacker, Player* defender);

	/**
	 * @brief allInMode War between both players until the attacker wins or cannot attack anymore
	 */
	void allInMode();
};


#endif // DICESREFEREE

