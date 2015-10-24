#ifndef COUNTRYLOST
#define COUNTRYLOST
#include "country.h"
class CountryLost{
private:
    Country* country;
    int lost;
public:
    CountryLost(Country& country,int lost);
    Country& getCountry();
    int getLosses();
};

#endif // COUNTRYLOST

