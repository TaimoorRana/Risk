#include "country.h"
#include "countrylost.h"
CountryLost::CountryLost(Country *country, int lost)
{
    this->country = country;
    this->lost = -lost;
}

Country *CountryLost::getCountry()
{
    return this->country;
}

int CountryLost::getLosses()
{
    return this->lost;
}
