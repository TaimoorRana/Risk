#include <iostream>
#include <string>
#include "continent.h"
#include "country.h"
#include "debug.h"
#include "map.h"

void debug(const std::string& string) {
	std::cout << "DEBUG: " << string << std::endl;
}

void map_print_continents(std::map<const std::string, Continent> map) {
	std::cout << "Continents: " << std::endl;
	for(auto const &ent1 : map) {
		// ent1.first is the first key
		Continent continent = ent1.second;
		std::cout << "  " << continent.getName();
		std::cout << " (" << continent.getReinforcementBonus() << ")";
		std::cout << std::endl;
	}
}

void map_print_countries(std::map<const std::string, Country> map) {
	std::cout << "Country: " << std::endl;
	for(auto const &ent1 : map) {
		// ent1.first is the first key
		Country country = ent1.second;
		Continent continent = country.getContinent();
		std::cout << "  " << country.getName() << " in continent " << continent.getName() << " with reinforcement bonus " << continent.getReinforcementBonus() << std::endl;
	}
}
