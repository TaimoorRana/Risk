#include <algorithm>
#include "debug.h"
#include "librisk.h"
#include "game_driver.h"

GameDriver* GameDriver::getInstance()
{
	static GameDriver* instance = nullptr;
	if (instance == nullptr) {
		instance = new GameDriver();
	}
	return instance;
}

void GameDriver::setCurrentPlayerName(const std::string& name) {
	this->currentPlayerName = name;
	this->notifyObservers();
}

std::string GameDriver::getCurrentPlayerName() const {
	return this->currentPlayerName;
}

Mode GameDriver::getCurrentMode() const {
	return this->currentMode;
}

void GameDriver::setCurrentMode(const Mode& mode) {
	this->currentMode = mode;
	this->notifyObservers();
}

void GameDriver::attackCountry(Country* attackerCountry, Country* defenderCountry) {
	int attackerArmy = attackerCountry->getArmies();
	int defenderArmy = defenderCountry->getArmies();
	int attackerDiceCount = 0;
	int defenderDiceCount = 0;

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
}

void GameDriver::attackPhase() {}

void GameDriver::reinforcePhase() {}

void GameDriver::fortificationPhase()
{
	// click on country to add to set
	// click again to remove
	// if array is full pop up the fortification dialog
	// display names of selected countries
	//fortificationDialog = fortificationDialog(c1);
}

void GameDriver::calculateReinforcementArmies(Player *p)
{
	// std::set<std::string> continents =p->getContinentsOwned();
	// std::set<std::string>::iterator itContinents = continents.begin();
	// int reinforcementArmies=0;
	// reinforcementArmies = p->getCountriesOwned().size()/3;
	// while(itContinents!= continents.end()){
	// 	reinforcementArmies += riskMap->getContinent(*itContinents)->getReinforcementBonus();
	// }
	// p->setReinforcements(reinforcementArmies);
}
