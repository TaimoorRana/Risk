#include <random>

#include "random.h"
void Random::whereToAttackFrom(RiskMap *map)
{
	listOfPlayerCountries= map->getCountriesOwnedByPlayer(getPlayer());
	auto l_iter = listOfPlayerCountries.begin();
	while (l_iter != listOfPlayerCountries.end()) {
		//if by chance soldier only has one army on territory cant attack
		if(map->getCountry(*l_iter)->getArmies()<=1){
			l_iter++;
			continue;
		}
		setAttackFrom(*l_iter,map->getCountry(*l_iter)->getArmies());
		if (decideAttackingCountry(map) == " " ) {
			l_iter++;
		}
		else{
			currentCountry = map->getCountry(*l_iter)->getName();
			countryToAttack = decideAttackingCountry(map);
			break;
		}

	}


}

std::string Random::decideAttackingCountry(RiskMap *map)
{
	countryToAttack = " ";
	attack = false;
	listOfAttackCountries =map->getNeighbours(getCountryAttackFrom());
	int borderCountries = listOfAttackCountries.size();
	int choice = rand()%borderCountries + 1;
	auto c_iter = listOfAttackCountries.begin();
	int count = 1;
	while (c_iter != listOfAttackCountries.end()) {
		if (!isSameOwner(map->getCountry(*c_iter)->getPlayer(), nameOfPlayer)&& map->getCountry(*c_iter)->getArmies()) {
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
