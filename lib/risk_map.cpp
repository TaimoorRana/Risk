#include "risk_map.h"

RiskMap::RiskMap(){}

bool RiskMap::adjacentCountries(const std::string& country_a, const std::string& country_b){
    return mapGraph.areAdjacent(country_a, country_b);
}

void RiskMap::addCountry( const std::string& name_country, const std::string& name_continent, int number_armies ){
    if(continents.find( name_continent) == continents.end() ){
        continents[name_continent] = Continent(name_continent);
        }
    if(countries.find( name_country) == countries.end() ){
        countries[name_country] = Country(name_continent, number_armies);
    }
    mapGraph.insertNode(name_country, name_continent);
}

void RiskMap::makeCountriesAdjacent(const std::string& country_a, const std::string& country_b){
    mapGraph.insertEdge(country_a, country_b);
}

void RiskMap::setPlayerOwner(const std::string& name_country, const std::string& name_player){
    countries.at(name_country).setPlayer(name_player);
}

std::string RiskMap::getPlayerOwner(const std::string& name_country){
    return countries.at(name_country).getPlayer();
}

void RiskMap::setArmies(const std::string& name_country, int armies){
    countries.at(name_country).setArmies(armies);
}

int RiskMap::getArmies(const std::string& name_country){
    return countries.at(name_country).getArmies();
}

std::string RiskMap::getContinentName(const std::string& name_country){
    return mapGraph.getSubgraphName(name_country);
}

Country* RiskMap::getCountryObj(std::string name_country){
    return &countries[name_country];
}

my_set RiskMap::listCountriesInsideContinent(const std::string& name_continent){
    return mapGraph.subgraphContents(name_continent);
}

my_set RiskMap::listOfNeighbours(const std::string& name_country){
    return mapGraph.incidentEdges(name_country);
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

RiskMap& RiskMap::getInstance(){
    static RiskMap* instance = nullptr;
    if (instance == nullptr) {
        instance = new RiskMap();
    }
    return *instance;
}



