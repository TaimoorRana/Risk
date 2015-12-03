#include "defensive.h"
#include <set>

/**
 * @brief Attack phase decision making
 */
std::pair<std::string, std::string> Defensive::attackPhase() {
	RiskMap* map = this->driver->getRiskMap();
	std::string playerName = this->driver->getCurrentPlayerName();
	std::set<std::string> countriesOwnedByPlayer = map->getCountriesOwnedByPlayer(playerName);

	std::pair<std::string, std::string> maxDifferencePair;
	int maxDifference = 0;

	for (const std::string &countryName : countriesOwnedByPlayer) {
		Country* country = map->getCountry(countryName);

		// Check if we have more armies than all of the neighbours opponents own
		bool moreArmiesThanNeighbours = true;
		for (const std::string &neighnourName : map->getNeighbours(country->getName())) {
			Country* neighbour = map->getCountry(neighnourName);
			if (neighbour->getPlayer() != playerName && neighbour->getArmies() > country->getArmies()) {
				moreArmiesThanNeighbours = false;
				break;
			}
		}

		// If we do, find the pair of countries with the greatest chance for success
		for (const std::string &neighnourName : map->getNeighbours(country->getName())) {
			Country* neighbour = map->getCountry(neighnourName);
			if (neighbour->getPlayer() != playerName) {
				int difference = neighbour->getArmies() - country->getArmies();
				if (difference >= maxDifference) {
					maxDifference = difference;
					maxDifferencePair = std::pair<std::string, std::string>(country->getName(), neighbour->getName());
				}
			}
		}
	}
	return maxDifferencePair;
}
