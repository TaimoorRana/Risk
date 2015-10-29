
#include "librisk.h"
#include "GraphADT.h"
#include "risk_map.h"


using namespace std;

int main() {

    RiskMap map;

    //Continent asia = Continent("Asia");
    Continent asia("Asia");

    map.addCountry("Persia",asia.getNameContinent(),1);

    map.addCountry("Arabia","Asia",2);
    map.addCountry("China","Asia",2);
    map.addCountry("India","Asia",1);
    map.addCountry("Russia","Europe",2);

    map.console_print_list_of_countries("Asia");
    map.console_print_list_of_countries("Europe");

    map.makeCountriesAdjacent("Arabia","Russia");
    map.makeCountriesAdjacent("Arabia","India");
    map.makeCountriesAdjacent("India","Persia");
    map.makeCountriesAdjacent("Persia","Arabia");
    map.makeCountriesAdjacent("Persia","Russia");
    map.makeCountriesAdjacent("China","Persia");
    map.makeCountriesAdjacent("India","China");

    if(map.adjacentCountries("India", "Russia"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    if(map.adjacentCountries("China", "Persia"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    map.console_print_list_of_neighbours("India");

    std::cout<<"Owner of Arabia: "<<map.getPlayerOwner("Arabia")<<std::endl;
    map.setPlayerOwner("Arabia","Adrianna");
    std::cout<<"Owner of Arabia: "<<map.getPlayerOwner("Arabia")<<std::endl;

    std::cout<<"Armies in Arabia: "<<map.getArmies("Arabia")<<std::endl;
    map.setArmies("Arabia", 10);
    std::cout<<"Armies in Arabia: "<<map.getArmies("Arabia")<<std::endl;

    std::cout<<"Country India belongs to: "<<map.getContinentName("India")<<std::endl;

    return 0;
}
