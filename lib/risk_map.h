#ifndef RISK_MAP
#define RISK_MAP

#include "country.h"
#include "GraphADT.h"
#include <map>

class RiskMap
{
    std::map<std::string, Continent> continents;
public:
    RiskMap() {}
    bool adjacentCountries(const Country&, const Country&);
    void addCountry(const std::string country, const std::string continent);

private:
    MySubGraph mapGraph;
};

#endif
