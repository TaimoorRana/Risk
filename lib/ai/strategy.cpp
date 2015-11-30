#include "strategy.h"

void Strategy::setPlayer(std::string nameOfPlayer)
{
	this->nameOfPlayer = nameOfPlayer;
}

void Strategy::setAttackFrom(std::string countryName, int numberOfArmiesOnTerritory)
{
	this->numberOfArmiesOnTerritory = numberOfArmiesOnTerritory;
	this->currentCountry = countryName;
}

std::string Strategy::getCurrentCountry()
{
	return currentCountry;
}

std::string Strategy::getCountryToAttack()
{
	return countryToAttack;
}

void Strategy::whereToAttackFrom(RiskMap *map)
{
	listOfPlayerCountries= map->getCountriesOwnedByPlayer(getPlayer());
	auto l_iter = listOfAttackCountries.begin();
	while (l_iter != listOfPlayerCountries.end()) {
		setAttackFrom(*l_iter,map->getCountry(*l_iter)->getArmies());
		if (decideAttackingCountry(map) == " " ) {
			l_iter++;
		}
		else{
			currentCountry = *l_iter;
			countryToAttack = decideAttackingCountry(map);
			break;
		}

	}


}

std::string Strategy::getCountryAttackFrom()
{
	return currentCountry;
}

bool Strategy::isSameOwner(std::string countryOwner1, std::string countryOwner2)
{
	return  countryOwner1 == countryOwner2;
}

int Strategy::getNumberOfArmies()
{
	return numberOfArmiesOnTerritory;
}

std::string Strategy::getPlayer()
{
	return nameOfPlayer;
}

void Strategy::setAttack(bool attack)
{
	this->attack = attack;
}
bool Strategy::isAttack(){
	return attack;
}

std::string Strategy::decideAttackingCountry(RiskMap *map)
{
	listOfAttackCountries = map->getNeighbours(getCountryAttackFrom());
	auto c_iter = listOfAttackCountries.begin();
	while (c_iter != listOfAttackCountries.end()) {
		if (map->getCountry(*c_iter)->getArmies() > 3 && !isSameOwner(*c_iter, nameOfPlayer)) {
		}
		c_iter++;
	}
	return " ";
}
