#ifndef DEBUG_H
#define DEBUG_H

#include <map>

void debug(const std::string& string);
void map_print_continents(std::map<const std::string, Continent> map);
void map_print_countries(std::map<const std::string, Country> map);

#endif // DEBUG_H
