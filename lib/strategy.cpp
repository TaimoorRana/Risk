#include "strategy.h"
#include <set>
#include <string>

Strategy::Strategy()
{

}

Strategy::~Strategy()
{

}

void Strategy::setPlayer(string nameOfPlayer)
{
    this->nameOfPlayer = nameOfPlayer;
}

void Strategy::setAttackFrom(string countryName, int numberOfArmiesOnTerritory)
{
    this->numberOfArmiesOnTerritory = numberOfArmiesOnTerritory;
    this->currentCountry = countryName;
}



string Strategy::getCountryAttackFrom()
{
    return currentCountry;
}

bool Strategy::isSameOwner(string countryOwner1, string countryOwner2)
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

string Strategy::decideAttackingCountry(RiskMap map)
{
    listOfAttackCountries = map.getNeighbours(getCountryAttackFrom());
    string_set ::const_iterator c_iter = listOfAttackCountries.begin();
    while (c_iter!=listOfAttackCountries.end()) {
        if(map.getCountry(*c_iter)->getArmies()>3 && !isSameOwner(*c_iter,nameOfPlayer)){

        }
        c_iter++;


    }
    return " ";
}

