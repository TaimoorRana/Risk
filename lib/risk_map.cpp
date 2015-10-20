#include "risk_map.h"

bool RiskMap::adjacentCountries(const Country& thisCountry, const Country& thatCountry){
    return mapGraph.areAdjacent(thisCountry.getName(), thatCountry.getName());
}

void RiskMap::addCountry(const std::string country_name, const std::string continent_name){
    //Create country
    //Create Continent
    mapGraph.insertVertex(country_name,continent_name);
}
