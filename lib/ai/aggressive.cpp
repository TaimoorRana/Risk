#include "aggressive.h"
#include <set>

std::pair<std::string, std::string> Aggressive::attackPhase() {
	RiskMap* map = this->driver->getRiskMap();
	std::string playerName = this->driver->getCurrentPlayerName();
	std::set<std::string> countriesOwnedByPlayer = map->getCountriesOwnedByPlayer(playerName);

	std::pair<std::string, std::string> maxDifferencePair("", "");
	int maxDifference = 0;

	for (const std::string &countryName : countriesOwnedByPlayer) {
		Country* country = map->getCountry(countryName);
		for (const std::string &neighbourName : map->getNeighbours(country->getName())) {
			Country* neighbour = map->getCountry(neighbourName);
			if (neighbour->getPlayer() != playerName) {
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
