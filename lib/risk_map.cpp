#include "risk_map.h"

bool RiskMap::adjacentCountries(const Country& thisCountry, const Country& thatCountry){
    return mapGraph.areAdjacent(thisCountry.getName(), thatCountry.getName());
}

void RiskMap::addCountry( const std::string& country_name, const std::string& continent_name ){
    if(continents.find( continent_name) == continents.end() ){
        continents[continent_name] = Continent(continent_name);
        }
    continents.at(continent_name).addCountry(country_name);
    mapGraph.insertVertex(country_name, continent_name);
}

void RiskMap::makeCountriesAdjacent(const std::string& country_a, const std::string& country_b){
    mapGraph.insertEdge(country_a,country_b);
}


std::unordered_map< std::string,Country > RiskMap::listCountriesInsideContinent(const std::string& name_continent){
    return continents.at(name_continent).getCountries();
}

void RiskMap::console_print_list_of_countries(const std::string& name_continent){
    std::cout<<"Countries in: "<<name_continent<<std::endl;

//    std::unordered_map< std::string, Country> list1 = listCountriesInsideContinent(name_continent);
//    std::unordered_map< std::string, Country>::const_iterator c_iter = list1.begin();
//    while ( c_iter != list1.end() ){
//        std::cout<<"\t\t"<< c_iter->first<<std::endl;
//        c_iter++;
//    }

    my_set countriesInside(mapGraph.subgraphContents(name_continent));
    my_set::const_iterator c_iter = countriesInside.begin();
    while (c_iter != countriesInside.end() ){
        std::cout<<"\t\t"<< *c_iter<<std::endl;
        c_iter++;
    }


}

