#include "strategy.h"
#include "aggressive.h"
#include <set>
#include <string>
#include <iostream>
using namespace std;

Aggressive::Aggressive()
{

}

Aggressive::~Aggressive()
{

}

string Aggressive::decideAttackingCountry(RiskMap map)
{
    attack = false;
    int differenceInArmies=0;
    listOfAttackCountries = map.getNeighbours(getCountryAttackFrom());
    string_set ::const_iterator c_iter = listOfAttackCountries.begin();
    while (c_iter!=listOfAttackCountries.end()) {

        if(map.getCountry(*c_iter)->getArmies()< getNumberOfArmies() && !isSameOwner(map.getCountry(*c_iter)->getPlayer(),nameOfPlayer)){
            if(getNumberOfArmies() - map.getCountry(*c_iter)->getArmies()>differenceInArmies){
                differenceInArmies = map.getCountry(*c_iter)->getArmies()-getNumberOfArmies();
                countryToAttack = *c_iter;
                attack =true;
            }
            //do nothing
            else{

            }
        }
        c_iter++;


    }
    return countryToAttack;
}

