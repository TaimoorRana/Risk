#include <random>

#include "random.h"

std::string Random::decideAttackingCountry(RiskMap map)
{
	countryToAttack = "";
	attack = false;
	listOfAttackCountries =map.getNeighbours(getCountryAttackFrom());
	int borderCountries = listOfAttackCountries.size();
	int choice = rand()%borderCountries + 1;
	auto c_iter = listOfAttackCountries.begin();
	int count = 1;
	while (c_iter != listOfAttackCountries.end()) {
		if (!isSameOwner(map.getCountry(*c_iter)->getPlayer(), nameOfPlayer)) {
			countryToAttack = *c_iter;
			if (count == choice) {
				return countryToAttack = *c_iter;

			}
			else {

			}
		}
		count++;
		c_iter++;
	}
	return countryToAttack;
}
