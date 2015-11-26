#include <fstream>
#include <iostream>

#include <cereal/archives/xml.hpp>

#include "game_state.h"

// For builder pattern
#include <string>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include "game_modes.h"

/**
 * Simplified version of the buildMap() and buildGameDriver() that uses the
 * serialization to actually serialize the RiskMap itself, eliminating the need
 * for an elaborate builder pattern altogether. The actual map's is entirely
 * encapsulated, so the "builder" only needs one line to read it back.
 *
 * This approach will be used for our project.
 */
bool GameState::load(std::string path, GameDriver* driver, RiskMap* map) {
	map->setNotificationsEnabled(false);

	std::ifstream infile(path);
	cereal::XMLInputArchive input(infile);
	input(cereal::make_nvp("driver", *driver));
	input(cereal::make_nvp("map", *map));

	map->setNotificationsEnabled(true);
	map->notifyObservers();
	return true;
}

/**
 * Simplified version of the buildSaveFile() that serializes the RiskMap itself,
 * eliminating the need to reconstruct it wit the builder pattern altogether.
 *
 * This approach will be used for our project.
 */
bool GameState::save(std::string path, GameDriver* driver, RiskMap* map) {
	std::ofstream outfile(path);
	cereal::XMLOutputArchive output(outfile);
	output(cereal::make_nvp("driver", *driver));
	output(cereal::make_nvp("map", *map));
	return true;
}

/**
 ****************************************************************************
 */

/**
 * Builds a RiskMap object using its API after reading information back from a
 * savestate.
 *
 * This approach is included to demonstrate a more elaborate Builder pattern for
 * grading purposes in A3.
 */
RiskMap* buildMap(std::string path) {
	// Prepare local variables. We'll use these to build the new object.
	std::map<std::string, Continent> continents;
	std::map<std::string, Country> countries;
	std::map<std::string, Player> players;
	std::map<std::string, std::string> country_continents;

	// Read state from file into some local variables
	std::ifstream infile(path);
	cereal::XMLInputArchive input(infile);
	input(cereal::make_nvp("continents", continents));
	input(cereal::make_nvp("countries", countries));
	input(cereal::make_nvp("players", players));
	input(cereal::make_nvp("country_continents", country_continents));

	// Configure a blank RiskMap object that we'll start to build.
	RiskMap* map = new RiskMap();

	// Configure the map's continents
	for (auto const &ent1 : continents) {
		const Continent& continent = ent1.second;
		map->addContinent(continent);
	}

	// Configure the map's countries
	for (auto const &ent1 : countries) {
		const Country& country = ent1.second;
		std::string continentName = country_continents.at(country.getName());
		map->addCountry(country, continentName);
	}

	// Configure the map's players
	for (auto const &ent1 : players) {
		const Player& player = ent1.second;
		map->addPlayer(player);
	}

	// The map is now ready to go, and it's internal state reflects the serialized
	// data read in from the savestate file.
	return map;
}

/**
 * Obtains the Singleton reference to the application's GameDriver and builds it
 * based on the save state.
 *
 * This approach is included to demonstrate a more elaborate Builder pattern for
 * grading purposes in A3.
 */
GameDriver* buildGameDriver(std::string path) {
	// Prepare local variables. We'll use these to build the new object.
	Mode currentMode;
	std::string currentPlayer;

	// Read state from file into some local variables
	std::ifstream infile(path);
	cereal::XMLInputArchive input(infile);
	input(cereal::make_nvp("currentMode", currentMode));
	input(cereal::make_nvp("currentPlayer", currentPlayer));

	// Because GameDriver is a singleton, we won't construct a new one - we'll
	// just get the global instance to work on.
	GameDriver* driver = GameDriver::getInstance();
	driver->setCurrentPlayerName(currentPlayer);
	driver->setCurrentMode(currentMode);
	return driver;
}

/**
 * Serializes information to a savestate. Can be read later to re-construct game
 * state using a builder pattern.
 *
 * This approach is included to demonstrate a more elaborate Builder pattern for
 * grading purposes in A3.
 */
bool buildSaveFile(std::string path, GameDriver* driver, RiskMap* map) {
	std::ofstream outfile(path);
	cereal::XMLOutputArchive output(outfile);
	output(cereal::make_nvp("continents", map->getContinents()));
	output(cereal::make_nvp("countries", map->getCountries()));
	output(cereal::make_nvp("players", map->getPlayers()));
	output(cereal::make_nvp("currentMode", driver->getCurrentPlayerName()));
	output(cereal::make_nvp("currentPlayer", driver->getCurrentMode()));
	return true;
}
