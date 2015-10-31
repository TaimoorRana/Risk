#ifndef DEBUG_H
#define DEBUG_H
#include <map>
#include "map.h"

void debug(const std::string& string);
void map_print_continents(std::map<const std::string, Continent*> countries);
void map_print_countries(std::map<const std::string, Country*> continents);
bool map_print_validation(Map* map);
bool map_validate_connected_graph(std::map<const std::string, Country*>& countries, Continent* limit_to);
void map_validate_connected_graph_visit(std::map<const Country*, bool>& visited, Country* country, Continent* limit_to);
#endif // DEBUG_H
