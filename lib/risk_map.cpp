#include "risk_map.h"

bool RiskMap::adjacentCountries(const std::string& thisCountry, const std::string& thatCountry){
    return mapGraph.areAdjacent(thisCountry, thatCountry);
}

void RiskMap::addCountry( const std::string& country_name, const std::string& continent_name ){
    if(continents.find( continent_name) == continents.end() ){
        continents[continent_name] = Continent(continent_name);
        }
    continents.at(continent_name).addCountry(country_name);
    mapGraph.insertNode(country_name, continent_name);
}

void RiskMap::makeCountriesAdjacent(const std::string& country_a, const std::string& country_b){
    mapGraph.insertEdge(country_a,country_b);
}



std::unordered_map< std::string,Country > RiskMap::listCountriesInsideContinent(const std::string& name_continent){
    return continents.at(name_continent).getCountries();
}

my_set RiskMap::listOfNeighbours(const std::string& country_name){
    return mapGraph.incidentEdges(country_name);
}

void RiskMap::console_print_list_of_neighbours(const std::string& name_country){
    std::cout<<"Neighbours of: "<<name_country<<std::endl;
    my_set neighbours(listOfNeighbours(name_country));
    my_set::const_iterator c_iter = neighbours.begin();
    while (c_iter != neighbours.end()) {
        std::cout<<"\t\t\t"<<*c_iter<<std::endl;
        c_iter++;
    }
}

void RiskMap::console_print_list_of_countries(const std::string& name_continent){
    std::cout<<"Countries in: "<<name_continent<<std::endl;
    my_set countriesInside(mapGraph.subgraphContents(name_continent));
    my_set::const_iterator c_iter = countriesInside.begin();
    while (c_iter != countriesInside.end() ){
        std::cout<<"\t\t"<< *c_iter<<std::endl;
        c_iter++;
    }
}




