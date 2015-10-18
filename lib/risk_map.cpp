#include "risk_map.h"

bool RiskMap::adjacentCountries(const Country& thisCountry, const Country& thatCountry){
    return mapGraph.areAdjacent(thisCountry.getName(), thatCountry.getName());
}

void RiskMap::insertCountry(const Country& country){
    mapGraph.insertVertex(country.getName());

}
