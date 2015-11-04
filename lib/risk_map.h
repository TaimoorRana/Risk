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
	SubGraphADT mapGraph;

public:
	RiskMap();
	~RiskMap();
	bool areCountriesAdjacent(const std::string& country_a, const std::string& country_b);
	void addCountry(const std::string& name_country, const std::string& name_continent, int number_armies);
	void addCountry(Country& country, const std::string& continentName);
	void addContinent(const std::string& name, int reinforcementBonus);
	void addContinent(Continent& continent);
	void addNeighbour(const std::string& country_a, const std::string& country_b);
	Continent* getContinentOfCountry(const std::string& name_country);
	Continent* getContinent(const std::string& name);
	Country* getCountry(const std::string& name_country);
	string_set getCountriesInContinent(const std::string& name_continent);
	string_set getNeighbours(const std::string& name_country);
	void consolePrintListOfNeighbours(const std::string& name_country);
	void consolePrintListOfCountries(const std::string& name_continent);
	static RiskMap* load(const std::string& path);
	void parse(const std::string& path);
	bool save(const std::string& path);
	void clear();
};
#endif
