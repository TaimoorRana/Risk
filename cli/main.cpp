#include "librisk.h"
#include "graph_adt.h"
#include "risk_map.h"

int main() {
    libriskInit();

    RiskMap map = RiskMap();

    Continent asia("Asia");

    Country c = Country("Persia");
    map.addCountry(c, asia.getName());

    c = Country("Arabia");
    map.addCountry(c, "Asia");
    c = Country("China");
    map.addCountry(c, "Asia");
    c = Country("India");
    map.addCountry(c, "Asia");
    c = Country("Russia");
    map.addCountry(c, "Europe");

    map.consolePrintListOfCountries("Asia");
    map.consolePrintListOfCountries("Europe");

    map.addNeighbour("Arabia","Russia");
    map.addNeighbour("Arabia","India");
    map.addNeighbour("India","Persia");
    map.addNeighbour("Persia","Arabia");
    map.addNeighbour("Persia","Russia");
    map.addNeighbour("China","Persia");
    map.addNeighbour("India","China");

    if(map.areCountriesAdjacent("India", "Russia"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    if(map.areCountriesAdjacent("China", "Persia"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    map.consolePrintListOfNeighbours("India");

    std::cout<<"Owner of Arabia: " << map.getCountry("Arabia")->getPlayer() << std::endl;
    map.getCountry("Arabia")->setPlayer("Adrianna");
    std::cout<<"Owner of Arabia: " << map.getCountry("Arabia")->getPlayer() << std::endl;

    std::cout << "Armies in Arabia: " << map.getCountry("Arabia")->getArmies() << std::endl;
    map.getCountry("Arabia")->setArmies(10);
    std::cout << "Armies in Arabia: " << map.getCountry("Arabia")->getArmies() << std::endl;

    std::cout << "Country India belongs to: " << map.getContinentOfCountry("India")->getName() << std::endl;

    map.save("riskmap_test0.map");
    return 0;
}
