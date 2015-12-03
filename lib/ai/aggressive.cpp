#include "aggressive.h"
#include <set>

/**
 * @brief Attack phase decision making
 */
std::pair<std::string, std::string> Aggressive::attackPhase() {
	RiskMap* map = this->driver->getRiskMap();
	std::string playerName = this->driver->getCurrentPlayerName();
	std::set<std::string> countriesOwnedByPlayer = map->getCountriesOwnedByPlayer(playerName);

	std::pair<std::string, std::string> maxDifferencePair("", "");
	int maxDifference = 0;

	// For each country we own, get its neighbours
	for (const std::string &countryName : countriesOwnedByPlayer) {
		Country* country = map->getCountry(countryName);
		for (const std::string &neighbourName : map->getNeighbours(country->getName())) {
			Country* neighbour = map->getCountry(neighbourName);
			if (neighbour->getPlayer() != playerName) {
				// If the neighbour is under the opponent's control, keep track of the
				// one with the lowest number of armies
				int difference = country->getArmies() - neighbour->getArmies();
				if (difference >= maxDifference) {
					maxDifference = difference;
					maxDifferencePair = std::pair<std::string, std::string>(country->getName(), neighbour->getName());
				}
			}
		}
	}
	return maxDifferencePair;
}
