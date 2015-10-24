#include <utility> // declares std, but not std::cout

#include "librisk.h"
#include "GraphADT.h"
#include "risk_map.h"

using namespace std;

int main() {
	cout << "This is a call to the library function: \n";
	librisk_print_todo();

    RiskMap map;

    Continent asia = Continent("Asia");
    map.addCountry("Persia",asia.getName());
    map.addCountry("Arabia","Asia");
    map.addCountry("China","Asia");
    map.addCountry("India","Asia");
    map.addCountry("Russia","Europe");

    map.console_print_list_of_countries("Asia");
    map.console_print_list_of_countries("Europe");


    map.makeCountriesAdjacent("Arabia","Russia");


	return 0;
}
