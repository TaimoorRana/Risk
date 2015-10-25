#ifndef RISK_MAP
#define RISK_MAP

#include "country.h"
#include "GraphADT.h"
#include <unordered_map>

class RiskMap
{
    std::unordered_map<std::string, Continent> continents;
    MySubGraph mapGraph;

public:
    RiskMap() {}
    bool adjacentCountries(const std::string&, const std::string&);
    void addCountry(const std::string&, const std::string&);
    void makeCountriesAdjacent(const std::string&, const std::string&);
    std::unordered_map< std::string, Country > listCountriesInsideContinent(const std::string&);
    void console_print_list_of_neighbours(const std::string& name_country);
    void console_print_list_of_countries(const std::string&);
    my_set listOfNeighbours(const std::string&);

};

#endif
