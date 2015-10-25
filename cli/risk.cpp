#include <utility> // declares std, but not std::cout

#include "librisk.h"
#include "GraphADT.h"
#include "risk_map.h"

using namespace std;

int main() {
	cout << "This is a call to the library function: \n";
	librisk_print_todo();

    RiskMap map;

    //Continent asia = Continent("Asia");
    Continent asia("Asia");

    map.addCountry("Persia",asia.getName());

    //asia.setName("Adrianna");

    map.addCountry("Arabia","Asia");
    map.addCountry("China","Asia");
    map.addCountry("India","Asia");
    map.addCountry("Russia","Europe");

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

    map.console_print_list_of_neighbours("India");
    
	return 0;
}
