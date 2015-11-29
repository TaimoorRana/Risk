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
