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
    RiskMap();
    MySubGraph mapGraph;

public:
    static RiskMap& getInstance();
    bool adjacentCountries(const std::string&, const std::string&);
    void addCountry(const std::string&, const std::string&, int);
    void makeCountriesAdjacent(const std::string&, const std::string&);
    Continent* getContinentOfCountry(const std::string&);
    Continent* getContinent(const std::string&);
    Country* getCountry(std::string);
    my_set listCountriesInsideContinent(const std::string&);
    void console_print_list_of_neighbours(const std::string&);
    void console_print_list_of_countries(const std::string&);
    my_set listOfNeighbours(const std::string&);
};
#endif
