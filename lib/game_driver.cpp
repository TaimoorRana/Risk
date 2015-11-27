#include <algorithm>
#include "debug.h"
#include "librisk.h"
#include "game_driver.h"

/**
 * @brief Returns the singleton instance of the GameDriver
 */
GameDriver* GameDriver::getInstance()
{
	static GameDriver* instance = nullptr;
	if (instance == nullptr) {
		instance = new GameDriver();
	}
	return instance;
}

/**
 * @brief Sets the name of the player whose turn is active
 */
void GameDriver::setCurrentPlayerName(const std::string& name) {
	this->currentPlayerName = name;
	this->notifyObservers();
}

/**
 * @brief Gets the name of the player whose turn is active
 */
std::string GameDriver::getCurrentPlayerName() const {
	return this->currentPlayerName;
}

/**
 * @brief Sets the current game phase
 */
Mode GameDriver::getCurrentMode() const {
	return this->currentMode;
}

/**
 * @brief Sets the current game phase
 */
void GameDriver::setCurrentMode(const Mode& mode) {
	this->currentMode = mode;
	this->notifyObservers();
}

/**
 * @brief Perform an attack move on a country
 */
bool GameDriver::attackCountry(Country* attackerCountry, Country* defenderCountry) {
	int attackerArmy = attackerCountry->getArmies();
	int defenderArmy = defenderCountry->getArmies();
	int attackerDiceCount = 0;
	int defenderDiceCount = 0;

	if (attackerArmy == 1 || attackerCountry->getPlayer() == defenderCountry->getPlayer()) {
		return false;
	}

	while (attackerArmy > 1 && defenderArmy > 0) {
		attackerDiceCount = attackerArmy > 3 ? 3 : attackerArmy - 1;
		defenderDiceCount = defenderArmy > 1 ? 2 : 1;
		std::vector<int> attackerDiceRolls = rollDice(attackerDiceCount);
		std::vector<int> defenderDiceRolls = rollDice(defenderDiceCount);

		int attackerLosses = 0;
		int defenderLosses = 0;

		// Compare attacker's highest to Defender's highest dice roll
		int dicesToCompare = std::min(attackerDiceRolls.size(), defenderDiceRolls.size());
		for (int i = 0; i < dicesToCompare; i++){
			debug("Defender rolled " + std::to_string(defenderDiceRolls[i]) + ", attacker rolled " + std::to_string(attackerDiceRolls[i]));
			if (attackerDiceRolls[i] > defenderDiceRolls[i]) {
				defenderLosses++;
			}
			else {
				attackerLosses++;
			}
		}

		// Remove soldiers lost from the battle
		attackerArmy -= attackerLosses;
		debug("Attacker lost " + std::to_string(attackerLosses) + " armies");

		defenderArmy -= defenderLosses;
		debug("Defender lost " + std::to_string(defenderLosses) + " armies");
	}

	if (defenderArmy <= 0) {
		// Attacker victorious: hand over ownership to the attacking player
		debug("Attacker won!");
		attackerCountry->setArmies(attackerArmy - 1);
		defenderCountry->setArmies(1);
		defenderCountry->setPlayer(attackerCountry->getPlayer());
	}
	else {
		// Defender victorious: reconfigure armies
		debug("Defender won!");
		attackerCountry->setArmies(attackerArmy);
		defenderCountry->setArmies(defenderArmy);
	}
	return true;
}

/**
 * @brief Perform an fortify move on a country
 */
bool GameDriver::fortifyCountry(Country* originCountry, Country* destinationCountry, int armies) {
	if (originCountry->getArmies() - armies <= 1) {
		return false;
	}
	originCountry->removeArmies(armies);
	destinationCountry->addArmies(armies);
	return true;
}

/**
 * @brief Calculates the number of reinforcements a player should receive.
 */
void GameDriver::calculateReinforcementArmies(Player* player)
{
	// std::set<std::string> continents = player->getContinentsOwned();
	// std::set<std::string>::iterator itContinents = continents.begin();
	// int reinforcementArmies=0;
	// reinforcementArmies = player->getCountriesOwned().size()/3;
	// while(itContinents!= continents.end()){
	// 	reinforcementArmies += riskMap->getContinent(*itContinents)->getReinforcementBonus();
	// }
	// player->setReinforcements(reinforcementArmies);
}
