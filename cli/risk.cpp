#include <iostream>
#include "librisk.h"
#include "map.h"
#include "debug.h"

void print_help(char *argv[]) {
	std::cout << "Usage: risk-a1-cli filename.map" << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Error: missing map filename." << std::endl << std::endl;
		print_help(argv);
		return 1;
	}

	Map* map = Map::load(argv[1]);
	if (map == NULL) {
		std::cout << "Error: map file '" << argv[1] << "' not found or is invalid." << std::endl << std::endl;
		print_help(argv);
		return 1;
	}

	map_print_continents(map->continents);
	map_print_countries(map->countries);

	delete map;

	return 0;
}
