#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include "map.h"
#include "debug.h"

#define MAP_PARSE_MODE_MAP 1
#define MAP_PARSE_MODE_CONTINENTS 2
#define MAP_PARSE_MODE_COUNTRIES 3

Map::Map() {
	this->continents = std::map<const std::string, Continent*>();
  this->countries = std::map<const std::string, Country*>();
  this->players = std::map<const std::string, Player*>();
}

Map::Map(const Map& map) {
	this->continents = std::map<const std::string, Continent*>(map.continents);
  this->countries = std::map<const std::string, Country*>(map.countries);
  this->players = std::map<const std::string, Player*>(map.players);
}

Map::~Map() {
	this->disableNotify = true;
	this->clear();
}

void Map::clear() {
	this->continents.clear();
	this->countries.clear();
	this->notifyObservers();
}

Continent* Map::getContinent(const std::string& name) {
	std::string debug_str = "Looking up continent: ";
	debug_str.append(name);
	debug(debug_str);

	return this->continents.at(name);
}
void Map::addContinent(Continent* continent) {
	this->continents.insert(std::pair<const std::string, Continent*>(continent->getName(), continent));
	this->notifyObservers();
}

Country* Map::getCountry(const std::string& name) {
	return this->countries.at(name);
}
void Map::addCountry(Country* country) {
	this->countries.insert(std::pair<const std::string, Country*>(country->getName(), country));
	Continent* continent = country->getContinent();
	continent->addCountry(country);
	for (Observer* observer : observers) {
		country->attachObserver(observer);
  }
	this->notifyObservers();
}

Player* Map::getPlayer(const std::string& name) {
	return this->players.at(name);
}
void Map::addPlayer(Player* player) {
	this->players.insert(std::pair<const std::string, Player*>(player->getName(), player));
	this->notifyObservers();
}

void Map::parse(const std::string& path) {
	this->disableNotify = true;
	this->clear();

	std::ifstream infile(path);
	std::string line;
	int mode = 0;

	while (std::getline(infile, line))
	{
		std::string debug_str("Read line: ");
		debug_str.append(line);
		debug(debug_str);
		// Windows prefers /r/n, but getline() breaks only on \n.
		if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

		// Set the mode for how we should process lines based on section headers
		if (line.compare("[Map]") == 0) {
			mode = MAP_PARSE_MODE_MAP;
			debug("  Parsing map metadata");
			continue;
		}
		if (line.compare("[Continents]") == 0) {
			mode = MAP_PARSE_MODE_CONTINENTS;
			debug("  Parsing continents");
			continue;
		}
		if (line.compare("[Territories]") == 0) {
			mode = MAP_PARSE_MODE_COUNTRIES;
			debug("  Parsing countries");
			continue;
		}

		// Process lines per the current mode.
		std::string item;
		std::stringstream line_stream(line);
		std::vector<std::string> values;
	  if (mode == MAP_PARSE_MODE_MAP || line.length() == 0) {
			debug_str = "  Skipping: ";
			debug_str.append(line);
			debug(debug_str);
			continue;
		}
		else if (mode == MAP_PARSE_MODE_CONTINENTS) {
			while (std::getline(line_stream, item, '=')) {
				values.push_back(item);
			}
			debug_str = "  Adding continent: ";
			debug_str.append(values[0]);
			debug(debug_str);

			Continent* continent = new Continent(values[0], atoi(values[1].c_str()));
			this->addContinent(continent);
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			Continent* continent = this->getContinent(values[3]);

			debug_str = "  Adding country: ";
			debug_str.append(values[0]);
			debug_str.append(" in continent ");
			debug_str.append(continent->getName());
			debug(debug_str);

			Country* country = new Country(values[0], continent, atoi(values[1].c_str()), atoi(values[2].c_str()));

			this->addCountry(country);
		}
		else {
			debug("Error parsing line: " + line);
			return;
		}
	}

	debug("Parsing file again to configure adjacencies");
	infile.clear();
	infile.seekg(0, std::ios_base::beg);
	while (std::getline(infile, line))
	{
		std::string debug_str("Read line: ");
		debug_str.append(line);
		debug(debug_str);
		// Windows prefers /r/n, but getline() breaks only on \n.
		if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

		// Set the mode for how we should process lines based on section headers
		if (line.compare("[Map]") == 0) {
			mode = MAP_PARSE_MODE_MAP;
			debug("  Parsing map metadata");
			continue;
		}
		if (line.compare("[Continents]") == 0) {
			mode = MAP_PARSE_MODE_CONTINENTS;
			debug("  Parsing continents");
			continue;
		}
		if (line.compare("[Territories]") == 0) {
			mode = MAP_PARSE_MODE_COUNTRIES;
			debug("  Parsing countries");
			continue;
		}

		// Process lines per the current mode.
		std::string item;
		std::stringstream line_stream(line);
		std::vector<std::string> values;
	  if (mode != MAP_PARSE_MODE_COUNTRIES || line.length() == 0) {
			debug_str = "  Skipping: ";
			debug_str.append(line);
			debug(debug_str);
			continue;
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			Country* country = this->getCountry(values[0]);
			std::vector<std::string>::iterator iter;
			for (iter = values.begin() + 4; iter < values.end(); iter++) {
				Country* neighbour = this->getCountry(*iter);
				country->addNeighbour(neighbour);

				debug_str = "  ";
				debug_str.append(country->getName());
				debug_str.append(" touches ");
				debug_str.append(neighbour->getName());
				debug(debug_str);
			}
		}
		else {
			debug("Error parsing line: " + line);
			return;
		}
	}

	debug("Finished parsing: " + path);
	this->disableNotify = false;
	this->notifyObservers();
}

Map* Map::load(const std::string& path) {
	struct stat buffer;
	bool exists = (stat (path.c_str(), &buffer) == 0);

	if (!exists) {
		return NULL;
	}

	Map* map = new Map();
	map->parse(path);
	return map;
}

bool Map::save(const std::string& path) {
	std::string debug_str("Saving map file to ");
	debug_str.append(path);
	debug(debug_str);
	std::ofstream outfile(path, std::ios::out);
	if (!outfile.is_open()) {
		return false;
	}

	outfile << "[Continents]" << std::endl;
	for (auto const &ent1 : this->continents) {
		Continent* continent = ent1.second;
		outfile << continent->getName() << "=" << continent->getReinforcementBonus() << std::endl;
	}
	outfile << std::endl;

	outfile << "[Territories]" << std::endl;
	for (auto const &ent1 : this->countries) {
		Country* country = ent1.second;
		Continent* continent = country->getContinent();
		outfile << country->getName() << "," << country->getPositionX() << "," << country->getPositionY() << "," << continent->getName();
		for (auto const &neighbour_country : country->getNeighbours()) {
			outfile << "," << neighbour_country->getName();
		}
		outfile << std::endl;
	}
	outfile << std::endl;

	outfile.close();
	return true;
}

void Map::notifyObservers() {
	if (this->disableNotify) {
		return;
	}
	Observable::notifyObservers();
}
