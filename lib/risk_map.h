#ifndef RISK_MAP
#define RISK_MAP

#include "country.h"
#include "GraphADT.h"

class RiskMap
{
public:
    RiskMap() {}
    bool adjacentCountries(const Country&, const Country&);
    void insertCountry(const Country& country);

private:
    MyGraph mapGraph;
//    std::vector<Continent> continents;
};

#endif
