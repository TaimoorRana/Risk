#include <iostream>
#include "librisk.h"
#include "map.h"
#include "debug.h"

void print_help(char *argv[]) {
	std::cout << "Usage: risk-a1-cli filename.map" << std::endl;
}

int main(int argc, char *argv[]) {
	int retval = 0;
	if (argc == 1) {
		std::cout << "Error: missing map filename." << std::endl << std::endl;
		print_help(argv);
		return 1;
	}

	std::string path(argv[1]);
	Map* map = Map::load(path);
	if (map == NULL) {
		std::cout << "Error: map file '" << argv[1] << "' not found or is invalid." << std::endl << std::endl;
		print_help(argv);
		return 1;
	}

	map_print_continents(map->continents);
	map_print_countries(map->countries);

	retval = map_print_validation(map);
	if (retval) {
		path.append(".new");
		Map::save(path, *map);
	}

	delete map;
	return retval;
}
