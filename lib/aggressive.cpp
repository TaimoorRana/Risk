#include "aggressive.h"
#include <set>
#include <string>

Aggressive::Aggressive()
{

}

Aggressive::~Aggressive()
{

}

string Aggressive::decideAttackingCountry(RiskMap map)
{
    int differenceInArmies=0;
    listOfAttackCountries = map.getNeighbours(getCountryAttackFrom());
    string_set ::const_iterator c_iter = listOfAttackCountries.begin();
    while (c_iter!=listOfAttackCountries.end()) {
        if(map.getCountry(*c_iter)->getArmies()< getNumberOfArmies() && !isSameOwner(*c_iter,nameOfPlayer)){
            if(getNumberOfArmies() - map.getCountry(*c_iter)->getArmies()>differenceInArmies){
                differenceInArmies = map.getCountry(*c_iter)->getArmies()-getNumberOfArmies();
                countryToAttack = *c_iter;
            }
            //do nothing
            else{

            }
        }
        c_iter++;


    }
    return countryToAttack;
}

