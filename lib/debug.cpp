#include <iostream>
#include <string>
#include "continent.h"
#include "country.h"
#include "debug.h"

void debug(const std::string& string) {
	std::cout << "DEBUG: " << string << std::endl;
}

void map_print_continents(std::map<const std::string, Continent*> continents) {
	std::cout << "Continents: " << std::endl;
	for (auto const &ent1 : continents) {
		// ent1.first is the first key
		Continent* continent = ent1.second;
		std::cout << "  " << continent->getName();
		std::cout << " (bonus " << continent->getReinforcementBonus() << ") size " << continent->getCountries().size();
		std::cout << std::endl;
	}
}

void map_print_countries(std::map<const std::string, Country*> countries) {
	std::cout << "Country: " << std::endl;
	for (auto const &ent1 : countries) {
		// ent1.first is the first key
		Country* country = ent1.second;
		Continent* continent = country->getContinent();
		std::cout << "  " << country->getName() << " in continent " << continent->getName() << " with reinforcement bonus " << continent->getReinforcementBonus() << " neighbouring on " << country->getNeighbours().size() << " countries" << std::endl;
	}
}

bool map_print_validation(Map* map) {
	bool result;

	result = map_validate_connected_graph(map->countries, NULL);
	if (!result) {
		std::cout << "ERROR: Countries are not a connected graph." << std::endl;
		return false;
	}
	std::cout << "Countries are a connected graph: " << (result ? "Yes" : "No") << std::endl;

	std::cout << "Checking continents are connected subgraphs... " << std::endl;
	for (auto const &ent1 : map->continents) {
		Continent* continent = ent1.second;
		result = map_validate_connected_graph(map->countries, continent);
		std::cout << "  " << continent->getName() << " is a subgraph? " << (result ? "Yes" : "No") << std::endl;
		if (!result) {
			std::cout << "ERROR: Continent " << continent->getName() << " is not a connected subgraph." << std::endl;
			return false;
		}
	}

	return true;
}

void map_validate_connected_graph_visit(std::map<const Country*, bool>& visited, Country* country, Continent* limit_to) {
	if (limit_to != NULL && country->getContinent() != limit_to) {
		return;
	}
	bool& was_visited = visited.at(country);
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour : country->getNeighbours()) {
		map_validate_connected_graph_visit(visited, neighbour, limit_to);
	}
}

bool map_validate_connected_graph(std::map<const std::string, Country*>& countries, Continent* limit_to) {
	std::map<const Country*, bool> visited = std::map<const Country*, bool>();
	for (auto const &ent1 : countries) {
		Country* country = ent1.second;

		if (limit_to != NULL && country->getContinent() != limit_to) {
			continue;
		}

		visited.insert(std::pair<const Country*, bool>(country, false));
	}

	Country* country = NULL;
	if (limit_to) {
		country = limit_to->getCountries().at(0);
	}
	else {
		country = countries.begin()->second;
	}
	map_validate_connected_graph_visit(visited, country, limit_to);

	for (auto const &ent1 : visited) {
		if (!ent1.second) {
			std::string debug_str = "Country ";
			Country country = *ent1.first;
			debug_str.append(country.getName());
			debug_str.append(" is not connected.");
			debug(debug_str);
			return false;
		}
	}

	return true;
}
