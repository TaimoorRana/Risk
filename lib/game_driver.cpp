#include <algorithm>
#include "debug.h"
#include "librisk.h"
#include "game_driver.h"

GameDriver::GameDriver(RiskMap* map) {
	this->map = map;
}

/**
 * @brief Gets the map associated to this instance.
 */
RiskMap* GameDriver::getRiskMap() {
	return this->map;
}

/**
 * @brief Sets the name of the player whose turn is active
 */
void GameDriver::setCurrentPlayerName(const std::string& name) {
	this->currentPlayerName = name;
	this->recalculateReinforcements();
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
		Player* winner = this->map->getPlayer(attackerCountry->getPlayer());
		winner->adjustBattlesWon(1);

		Player* loser = this->map->getPlayer(attackerCountry->getPlayer());
		loser->adjustBattlesLost(1);

		attackerCountry->setArmies(attackerArmy - 1);
		defenderCountry->setArmies(1);
		defenderCountry->setPlayer(attackerCountry->getPlayer());
		this->recalculateReinforcements();
	}
	else {
		// Defender victorious: reconfigure armies
		debug("Defender won!");
		Player* winner = this->map->getPlayer(defenderCountry->getPlayer());
		winner->adjustBattlesWon(1);

		Player* loser = this->map->getPlayer(attackerCountry->getPlayer());
		loser->adjustBattlesLost(1);

		attackerCountry->setArmies(attackerArmy - 1);
		attackerCountry->setArmies(attackerArmy);
		defenderCountry->setArmies(defenderArmy);
	}
	return true;
}

/**
 * @brief Perform an fortify move on a country
 */
bool GameDriver::fortifyCountry(Country* originCountry, Country* destinationCountry, int armies) {
	if (originCountry->getArmies() - armies <= 0) {
		return false;
	}
	originCountry->removeArmies(armies);
	destinationCountry->addArmies(armies);
	return true;
}

/**
 * @brief Adjusts each player's reinforcement count
 */
void GameDriver::recalculateReinforcements() {
	for (auto const &ent1: this->map->getPlayers()) {
		Player* player = this->map->getPlayer(ent1.first);
		// Players get reinfocements equal to their countries/3 (discard fractions),
		// down to a minimum of three reinforcements.
		int countryBonus = this->map->getCountriesOwnedByPlayer(player->getName()).size() / 3;
		int reinforcements = std::max(3, countryBonus);

		// Check for continent bonuses
		for (auto &continentName : this->map->getContinentsOwnedByPlayer(player->getName())) {
			Continent* continent = this->map->getContinent(continentName);
			reinforcements += continent->getReinforcementBonus();
		}
		player->setReinforcements(reinforcements);
	}
}
