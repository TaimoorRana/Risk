#include "strategy.h"
#include "random.h"

#include <random>
#include <set>
#include <iostream>
using namespace std;

Random::Random()
{

}

Random::~Random()
{

}

string Random::decideAttackingCountry(RiskMap map)
{
    countryToAttack = "";
    attack =false;
    listOfAttackCountries =map.getNeighbours(getCountryAttackFrom());
    int borderCountries = listOfAttackCountries.size();
    int choice = rand()%borderCountries +1;
    string_set ::const_iterator c_iter = listOfAttackCountries.begin();
    int count = 1;
    while(c_iter!=listOfAttackCountries.end()){

        if(!isSameOwner(map.getCountry(*c_iter)->getPlayer(),nameOfPlayer)){
            countryToAttack = *c_iter;
            if(count==choice){
                return countryToAttack = *c_iter;

            }

            else{

            }
        }
        count++;
        c_iter++;
    }
    return countryToAttack;

}

