#ifndef LIB_MAP_H
#define LIB_MAP_H

#include <string>
#include "continent.h"
#include "country.h"

class Map {
private:
  std::vector<Country> countries;
  std::vector<Continent> continents;
public:
	Map() {}
	static Map* load(const std::string& file);
};
#endif // LIB_MAP_H
