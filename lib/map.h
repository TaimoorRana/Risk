#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
#include "continent.h"
#include "country.h"

class Map {
private:

public:
	std::map<const std::string, Continent*> continents;
  std::map<const std::string, Country*> countries;
	Map();
	Map(const Map& map);
	~Map();
	static Map* load(const std::string& path);
	static bool save(const std::string& path, const Map& map);
	Continent* getContinent(const std::string name);
	void addContinent(Continent* continent);
	Country* getCountry(const std::string name);
  void addCountry(Country* continent);
};
#endif // MAP_H
