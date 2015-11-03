#ifndef RISK_MAP
#define RISK_MAP

#include <unordered_map>

#include "country.h"
#include "continent.h"
#include "GraphADT.h"

class RiskMap
{
private:
	std::unordered_map<std::string, Continent> continents;
	std::unordered_map<std::string, Country> countries;
	SubGraphADT mapGraph;

public:
	RiskMap();
	bool areCountriesAdjacent(const std::string& country_a, const std::string& country_b);
	void addCountry(const std::string& name_country, const std::string& name_continent, int number_armies);
	void addNeighbour(const std::string& country_a, const std::string& country_b);
	Continent* getContinentOfCountry(const std::string& name_country);
	Continent* getContinent(const std::string& name_continent);
	Country* getCountry(const std::string& name_country);
	string_set getCountriesInContinent(const std::string& name_continent);
	string_set getNeighbours(const std::string& name_country);
	void consolePrintListOfNeighbours(const std::string& name_country);
	void consolePrintListOfCountries(const std::string& name_continent);
};
#endif
