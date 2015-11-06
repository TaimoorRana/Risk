#ifndef RANDOM_H
#define RANDOM_H
#include <string>
#include <vector>
#include <set>
#include "strategy.h"


class Random :public Strategy
{
public:
    Random();
    ~Random();
    string decideAttackingCountry(set<string> listOfAttackCountries);
};

#endif // RANDOM_H
