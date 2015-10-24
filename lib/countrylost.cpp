#include "country.h"
#include "countrylost.h"
CountryLost::CountryLost(Country& country, int lost)
{
    this->country = &country;
    this->lost = -lost;
}

Country& CountryLost::getCountry()
{
    Country* ptrCountry = this->country;
    return *ptrCountry;
}

int CountryLost::getLosses()
{
    return this->lost;
}
