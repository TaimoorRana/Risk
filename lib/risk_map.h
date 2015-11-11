#ifndef RISK_MAP
#define RISK_MAP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <unordered_map>

#include "country.h"
#include "continent.h"
#include "graph_adt.h"
#include "player.h"
#include "observable.h"

#define MAP_PARSE_MODE_MAP 1
#define MAP_PARSE_MODE_CONTINENTS 2
#define MAP_PARSE_MODE_COUNTRIES 3

class RiskMap : public Observable
{
private:
	bool disableNotify = false;
	std::unordered_map<std::string, Continent> continents;
	std::unordered_map<std::string, Country> countries;
	std::unordered_map<std::string, Player> players;
	SubGraphADT mapGraph;

public:
	RiskMap();
	~RiskMap();
	bool areCountriesAdjacent(const std::string& country_a, const std::string& country_b);
	Country* addCountry(const std::string& name_country, const std::string& name_continent, int number_armies);
	Country* addCountry(const Country& country, const std::string& continentName);
	void addContinent(const std::string& name, int reinforcementBonus);
	void addContinent(const Continent& continent);
	void remCountry(const Country& country);
	void addNeighbour(const std::string& country_a, const std::string& country_b);
	void remNeighbour(const std::string& country_a, const std::string& country_b);

	void addPlayer(const Player& player);
	Continent* getContinentOfCountry(const std::string& name_country);
	Continent* getContinent(const std::string& name);
	Country* getCountry(const std::string& name_country);
	string_set getCountriesInContinent(const std::string& name_continent);
	string_set getNeighbours(const std::string& name_country);
	Player* getPlayer(const std::string& playerName);
	const std::unordered_map<std::string, Continent>& getContinents() const;
	const std::unordered_map<std::string, Country>& getCountries() const;
	const std::unordered_map<std::string, Player>& getPlayers() const;
	void consolePrintListOfNeighbours(const std::string& name_country);
	void consolePrintListOfCountries(const std::string& name_continent);
	static RiskMap* load(const std::string& path);
	void parse(const std::string& path);
	bool save(const std::string& path);
	void clear();
	bool validate();
	void isConnectedGraphHelper(std::unordered_map<const Country*, bool>& visited, Country* country, const std::string& limit_to);
	bool isConnectedGraph(const std::string& limit_to);
	void notifyObservers();
};
#endif
