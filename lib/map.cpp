#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "map.h"
#include "debug.h"

#define MAP_PARSE_MODE_MAP 1
#define MAP_PARSE_MODE_CONTINENTS 2
#define MAP_PARSE_MODE_COUNTRIES 3

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
		// Windows prefers /r/n, but getline() breaks only on \n.
		if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

		// Set the mode for how we should process lines based on section headers
		if (line.compare("[Map]") == 0) {
			mode = MAP_PARSE_MODE_MAP;
			continue;
		}
		if (line.compare("[Continents]\n") == 0) {
			mode = MAP_PARSE_MODE_CONTINENTS;
			continue;
		}
		if (line.compare("[Territories]\n") == 0) {
			mode = MAP_PARSE_MODE_COUNTRIES;
			continue;
		}

		// Process lines per the current mode.
		std::string item;
		std::stringstream line_stream(line);
		std::vector<std::string> values;
		if (mode == MAP_PARSE_MODE_MAP) {
			continue;
		}
		else if (mode == MAP_PARSE_MODE_CONTINENTS) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			// TODO actual things
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			// TODO actual things
		}
		else {
			debug("Error parsing line: " + line);
			return NULL;
		}
	}

	return map;
}
