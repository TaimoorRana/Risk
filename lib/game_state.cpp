#include <fstream>
#include <iostream>

#include <cereal/archives/xml.hpp>

#include "game_state.h"

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

bool GameState::save(std::string path, GameDriver* driver, RiskMap* map) {
	std::ofstream outfile(path);
	cereal::XMLOutputArchive output(outfile);
	output(cereal::make_nvp("driver", *driver));
	output(cereal::make_nvp("map", *map));
	return true;
}
