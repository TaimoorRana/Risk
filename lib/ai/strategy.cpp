#include "strategy.h"
#include "librisk.h"

Strategy::Strategy() {
	this->driver = GameDriver::getInstance();
}

/**
 * @brief A signal sent to the Strategy class from the game driver to indicate
 * that a computer-controlled player should made their move.
 *
 * The AI strategy implementations override each of the fooPhase() methods
 * which return the name(s) of the country or countries to act upon.
 *
 * Empty string indicates the AI wishes to make no move, or there are none
 * possible.
 */
void Strategy::takeAction(Mode mode) {
	RiskMap* map = this->driver->getRiskMap();

	if (mode == REINFORCEMENT) {
		std::string countryName = this->reinforcePhase();
		if (countryName == "") {
			return;
		}
		Country* country = map->getCountry(countryName);
		Player* player = map->getPlayer(country->getPlayer());
		this->driver->reinforceCountry(player, country, player->getReinforcements());
	}
	else if (mode == ATTACK) {
		std::pair<std::string, std::string> countryNames = this->attackPhase();
		if (countryNames.first == "" || countryNames.second == "") {
			return;
		}
		driver->attackCountry(map->getCountry(countryNames.first), map->getCountry(countryNames.second));
	}
	else if (mode == FORTIFICATION) {
		std::pair<std::string, std::string> countryNames = this->fortifyPhase();
		if (countryNames.first == "" || countryNames.second == "") {
			return;
		}
		// Given the two countries, fortify so that the armies are as equal as possible.
		Country* origin = map->getCountry(countryNames.first);
		Country* destination = map->getCountry(countryNames.second);
		int splitDifference = std::abs(origin->getArmies() - destination->getArmies()) / 2;
		this->driver->fortifyCountry(origin, destination, splitDifference);
	}
}

/**
 * @brief Reinforcement phase decision making. Places all reinforcements on the
 * country with the fewest armies.
 */
std::string Strategy::reinforcePhase() {
	RiskMap* map = this->driver->getRiskMap();
	std::string playerName = this->driver->getCurrentPlayerName();

	int minArmies = 10000;
	Country* minArmiesCountry = nullptr;

	// add the reinforcements to the player
	int numCardsSelected = map->getPlayer(playerName)->getCards();
	int armiesEarned = convertCardsToReinforcements(numCardsSelected);
	if (armiesEarned > 0) {
		this->driver->addCardsTradeReinforcements(armiesEarned);
		this->driver->updatePlayerCards(-numCardsSelected);
	}

	// Reinforce the weakest country
	for (const std::string countryName : map->getCountriesOwnedByPlayer(playerName)) {
		Country* country = map->getCountry(countryName);
		int armies = country->getArmies();
		if (armies < minArmies) {
			minArmies = armies;
			minArmiesCountry = country;
		}
	}
	if (minArmiesCountry == nullptr) {
		return "";
	}
	return minArmiesCountry->getName();
}

/**
 * @brief Fortification phase decision making
 */
std::pair<std::string, std::string> Strategy::fortifyPhase() {
	// Not implemented in the current AI.
	return std::pair<std::string, std::string>("", "");
}
