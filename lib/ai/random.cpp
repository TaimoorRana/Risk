#include "random.h"
#include <algorithm>
#include <functional>
#include <random>
#include <vector>

/**
 * @brief Attack phase decision making
 */
std::pair<std::string, std::string> Random::attackPhase() {
	RiskMap* map = this->driver->getRiskMap();
	std::string playerName = this->driver->getCurrentPlayerName();

	// Copy the std::set of countries we own into a vector, then shuffle it
	std::vector<std::string> countriesOwnedByPlayer;
	for (const std::string countryName : map->getCountriesOwnedByPlayer(playerName)) {
		countriesOwnedByPlayer.push_back(countryName);
	}
	std::random_shuffle(std::begin(countriesOwnedByPlayer), std::end(countriesOwnedByPlayer));

	Country* origin = nullptr;
	Country* destination = nullptr;

	// Get a random country owned by us
	for (const std::string& randomCountryName : countriesOwnedByPlayer) {
		Country* country = map->getCountry(randomCountryName);

		// Copy the std::set of neighbours to a vector, then shuffle it
		std::vector<std::string> neighbours;
		for (const std::string neighbourName : map->getNeighbours(country->getName())) {
			neighbours.push_back(neighbourName);
		}
		std::random_shuffle(std::begin(neighbours), std::end(neighbours));

		// Get a the first randomized neighbour, ensuring we don't own it too
		for (const std::string& randomNeighbourName : neighbours) {
			Country* neighbour = map->getCountry(randomNeighbourName);
			if (neighbour->getPlayer() != playerName) {
				// If all is well, break out
				origin = country;
				destination = neighbour;
				break;
			}
		}

		// If all is well, break out - otherwise, we own all of this country's
		// neighbours! We need to pick another country we own by looping again.
		if (destination != nullptr) {
			break;
		}
	}

	if (origin == nullptr || destination == nullptr) {
		std::pair<std::string, std::string>("", "");
	}

	return std::pair<std::string, std::string>(origin->getName(), destination->getName());
}
