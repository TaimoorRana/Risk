#include "risk_map.h"

RiskMap::RiskMap(){}

bool RiskMap::areCountriesAdjacent(const std::string& country_a, const std::string& country_b){
    return mapGraph.areAdjacent(country_a, country_b);
}

void RiskMap::addCountry( const std::string& name_country, const std::string& name_continent, int number_armies ){
    if(continents.find( name_continent) == continents.end() ){
        continents[name_continent] = Continent(name_continent);
        }
    if(countries.find( name_country) == countries.end() ){
        countries[name_country] = Country(name_country, number_armies);
    }
    mapGraph.insertNode(name_country, name_continent);
}

void RiskMap::addNeighbour(const std::string& country_a, const std::string& country_b){
    mapGraph.insertEdge(country_a, country_b);
}

Continent* RiskMap::getContinentOfCountry(const std::string& name_country){
    std::string name_continent(mapGraph.getSubgraphName(name_country));
    return &continents[name_continent];
}

Continent* RiskMap::getContinent(const std::string& name_continent){
    return &continents[name_continent];
}

Country* RiskMap::getCountry(std::string name_country){
    return &countries[name_country];
}

string_set RiskMap::getCountriesInContinent(const std::string& name_continent){
    return mapGraph.subgraphContents(name_continent);
}

string_set RiskMap::getNeighbours(const std::string& name_country){
    return mapGraph.incidentEdges(name_country);
}

void RiskMap::console_print_list_of_neighbours(const std::string& name_country){
    std::cout<<"Neighbours of: "<<name_country<<std::endl;
    string_set neighbours(getNeighbours(name_country));
    string_set::const_iterator c_iter = neighbours.begin();
    while (c_iter != neighbours.end()) {
        std::cout<<"\t\t\t"<<*c_iter<<std::endl;
        c_iter++;
    }
}

void RiskMap::console_print_list_of_countries(const std::string& name_continent){
    std::cout<<"Countries in: "<<name_continent<<std::endl;
    string_set countriesInside(mapGraph.subgraphContents(name_continent));
    string_set::const_iterator c_iter = countriesInside.begin();
    while (c_iter != countriesInside.end() ){
        std::cout<<"\t\t"<< *c_iter<<std::endl;
        c_iter++;
    }
}

RiskMap& RiskMap::getInstance(){
    static RiskMap* instance = nullptr;
    if (instance == nullptr) {
        instance = new RiskMap();
    }
    return *instance;
}



