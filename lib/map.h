#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
#include "continent.h"
#include "country.h"
#include "observable.h"

class Map : public Observable {
private:
	bool disableNotify = false;
public:
	std::map<const std::string, Continent*> continents;
  std::map<const std::string, Country*> countries;
  std::map<const std::string, Player*> players;
	Map();
	Map(const Map& map);
	~Map();
	void clear();
	static Map* load(const std::string& path);
	void parse(const std::string& path);
	bool save(const std::string& path);
	Continent* getContinent(const std::string& name);
	void addContinent(Continent* continent);
	Country* getCountry(const std::string& name);
	void addPlayer(Player* player);
	Player* getPlayer(const std::string& name);
  void addCountry(Country* continent);
  void notifyObservers();
};
#endif // MAP_H
