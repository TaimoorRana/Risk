#include "defensive.h"

std::string Defensive::decideAttackingCountry(RiskMap *map)
{

	attack = false;
	listOfAttackCountries = map->getNeighbours(getCountryAttackFrom());
	auto c_iter = listOfAttackCountries.begin();
	while (c_iter!=listOfAttackCountries.end()) {
		if (map->getCountry(*c_iter)->getArmies() + twoAdditionalArmies < (getNumberOfArmies())
				&& !isSameOwner(map->getCountry(*c_iter)->getPlayer(), nameOfPlayer)){
			countryToAttack = *c_iter;
		}
		else {
			countryToAttack = " ";
			return countryToAttack;
		}
		c_iter++;
	}
	attack = true;
	return countryToAttack;
}

void Defensive::whereToAttackFrom(RiskMap *map)
{
	listOfPlayerCountries= map->getCountriesOwnedByPlayer(getPlayer());
	auto l_iter = listOfPlayerCountries.begin();
	while (l_iter != listOfPlayerCountries.end()) {
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

