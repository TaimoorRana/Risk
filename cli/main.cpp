
#include "librisk.h"
#include "GraphADT.h"
#include "risk_map.h"


using namespace std;

int main() {
	libriskInit();

	RiskMap map = RiskMap();

	//Continent asia = Continent("Asia");
	Continent asia("Asia");

	map.addCountry("Persia", asia.getName(), 1);

	map.addCountry("Arabia","Asia",2);
	map.addCountry("China","Asia",2);
	map.addCountry("India","Asia",1);
	map.addCountry("Russia","Europe",2);

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

	return 0;
}
