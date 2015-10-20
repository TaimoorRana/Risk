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

    map.addCountry("Ural",asia.getName());

	return 0;
}
