#ifndef RISK_MAP
#define RISK_MAP

#include <unordered_map>

#include "country.h"
#include "continent.h"
#include "GraphADT.h"

class RiskMap
{
    std::unordered_map<std::string, Continent> continents;
    std::unordered_map<std::string, Country> countries;
    
    MySubGraph mapGraph;

public:
    RiskMap() {}
    bool adjacentCountries(const std::string&, const std::string&);
    void addCountry(const std::string&, const std::string&, int);
    void makeCountriesAdjacent(const std::string&, const std::string&);
    void setPlayerOwner(const std::string&, const std::string&);
    std::string getPlayerOwner(const std::string&);
    void setArmies(const std::string&, int);
    int getArmies(const std::string&);
    std::string getContinentName(const std::string&);

    my_set listCountriesInsideContinent(const std::string&);
    void console_print_list_of_neighbours(const std::string&);
    void console_print_list_of_countries(const std::string&);
    my_set listOfNeighbours(const std::string&);
};
#endif
