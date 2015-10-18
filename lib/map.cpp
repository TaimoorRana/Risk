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

Continent Map::get_continent(const std::string name) {
	std::string debug_str = "Looking up continent: ";
	debug_str.append(name);
	debug(debug_str);

	Continent continent = this->continents.at(name);
	return continent;
}
void Map::add_continent(Continent continent) {
	this->continents.insert(std::pair<const std::string, Continent>(continent.getName(), continent));
}

Country Map::get_country(const std::string name) {
	Country country = this->countries.at(name);
	return country;
}
void Map::add_country(Country country) {
	this->countries.insert(std::pair<const std::string, Country>(country.getName(), country));
}

Map* Map::load(const std::string& path) {
	struct stat buffer;
	bool exists = (stat (path.c_str(), &buffer) == 0);

	if (!exists) {
		return NULL;
	}

	Map* map = new Map();

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
			map->add_continent(*continent);
			delete continent;
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			Continent continent = map->get_continent(values[3]);

			debug_str = "  Adding country: ";
			debug_str.append(values[0]);
			debug_str.append(" in continent ");
			debug_str.append(continent.getName());
			debug(debug_str);

			Country* country = new Country(values[0], continent, atoi(values[2].c_str()), atoi(values[3].c_str()));
			map->add_country(*country);
			delete country;
		}
		else {
			debug("Error parsing line: " + line);
			return NULL;
		}
	}

	debug("Finished parsing: " + path);

	return map;
}
