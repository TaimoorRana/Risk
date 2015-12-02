#include "strategy.h"

Strategy::Strategy() {
	this->driver = GameDriver::getInstance();
}

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

std::string Strategy::reinforcePhase() {
	RiskMap* map = this->driver->getRiskMap();

	int minArmies = 10000;
	Country* minArmiesCountry = nullptr;

	// Reinforce the weakest country
	for (const std::string countryName : map->getCountriesOwnedByPlayer(driver->getCurrentPlayerName())) {
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

std::pair<std::string, std::string> Strategy::fortifyPhase() {
	// Not implemented in the current AI.
	return std::pair<std::string, std::string>("", "");
}
