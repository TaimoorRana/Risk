#ifndef LIB_MAP_H
#define LIB_MAP_H

#include <string>
#include <map>
#include "continent.h"
#include "country.h"

class Map {
private:
  std::map<const std::string, Continent> continents;
  std::map<const std::string, Country> countries;
public:
	Map() {}
	~Map() {} // TODO
	static Map* load(const std::string& file);
	Continent get_continent(const std::string name);
	void add_continent(Continent* continent);
	Country get_country(const std::string name);
  void add_country(Country* continent);
};
#endif // LIB_MAP_H
