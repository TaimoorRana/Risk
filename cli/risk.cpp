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

	Continent continent = map->get_continent("Northern Islands");
	std::cout << "Continent: " << continent.getName();
	std::cout << " (" << continent.getReinforcementBonus() << ")";
	std::cout << std::endl;

	Country country = map->get_country("1");
	std::cout << "Country: " << country.getName();
	std::cout << " (" << country.getPositionX() << "," << country.getPositionY() << ") in continent " << country.getContinent().getName();
	std::cout << std::endl;

	delete map;

	return 0;
}
