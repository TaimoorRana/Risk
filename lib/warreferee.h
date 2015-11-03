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
	static const int MAX_DICES = 3;

	// Players
	std::string attackerPlayer;
	std::string defenderPlayer;

	// players armies
	int attackerArmy;
	int defenderArmy;

	int defenderDices;
	int attackerDices;

	/*
	 * Roll dices for both players and calculate Losses occured to each army;
	 */
	void calculateLossesHelper();

public:
	static WarReferee& getInstance();

	/*
	 Player related methods
	 @params string: player name
	 */
	void setAttackerPlayer(std::string&);
	void setDefenderPlayer(std::string&);
	void setBothPlayers(std::string& , std::string&);
	std::string getAttackerPlayer();
	std::string getDefenderPlayer();

	/*
	 Player Army related methods
	 @params int&: number of army
	 */
	void setDefenderArmy(int&);
	void setAttackerArmy(int&);
	void setBothArmies(int&,int&);
	int getAttackerArmy();
	int getDefenderArmy();


	/*
	 * Roll dices for both players and calculate Losses occured to each army - dices are assigned depending on the army size
	 */
	void calculateLosses();
	/*
	 * Roll dices for both players and calculate Losses occured to each army - dices amount is given by the user
	 * int: attacker Dices amount
	 * int: defender Dices amount
	 */
	void calculateLosses(int& , int& );

	/*
	 * Starts war between both players
	 * @string&: attacker Player
	 * @int&: attacker Army
	 * string&: defender Player
	 * int&: defender Army
	 */
	void startWar(std::string& ,int& ,std::string& ,int&);
	void allInMode();
};


#endif // DICESREFEREE

