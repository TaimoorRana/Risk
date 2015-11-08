#include "strategy.h"
#include "defensive.h"
#include <set>
#include <string>

Defensive::Defensive()
{

}

Defensive::~Defensive()
{

}


string Defensive::decideAttackingCountry(RiskMap map)
{
    attack =false;
    listOfAttackCountries = map.getNeighbours(getCountryAttackFrom());
    string_set::const_iterator c_iter = listOfAttackCountries.begin();
    while(c_iter!=listOfAttackCountries.end()){
        if(map.getCountry(*c_iter)->getArmies() <getNumberOfArmies()
                && !isSameOwner(map.getCountry(*c_iter)->getPlayer(),nameOfPlayer)){
            countryToAttack = *c_iter;

        }
        else{
            countryToAttack = "";

            return countryToAttack;
        }
        c_iter++;

    }
    attack = true;
    return countryToAttack;

}

