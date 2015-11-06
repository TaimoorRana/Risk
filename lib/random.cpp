#include "random.h"

Random::Random()
{

}

Random::~Random()
{

}

string Random::decideAttackingCountry(RiskMap map)
{
    attack =false;
    listOfAttackCountries =map.getNeighbours(getCountryAttackFrom());
    int borderCountries = listOfAttackCountries.size();
    string_set ::const_iterator c_iter = listOfAttackCountries.begin();
    return "";

}

