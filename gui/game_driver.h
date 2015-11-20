#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H
#include <string>

#include "player.h"

/**
 * @brief The GameDriver class
 * Handles the ordering of the game  the players turn the number of reinforcements
 * calculating the number of armies placed and allowed to place
 */
class GameDriver {
public:
	std::string getCurrentPlayerName() const;
	void setCurrentPlayerName(const std::string& name);

	/**
	 * @brief calculateReinforcementArmies calculates the reinforcements for the player using the continents and countries
	 * that the player owns.
	 * @param p the player pointer
	 *
	 */
	void calculateReinforcementArmies(Player *p);

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
	 * @brief getInstance gets the singleton instance of the gamedriver
	 * @return
	 */
	static GameDriver* getInstance();

private:
	bool canFortify = false;
	std::string currentPlayerName = "";
};

#endif // GAMEDRIVER_H
