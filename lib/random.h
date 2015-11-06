#ifndef RANDOM_H
#define RANDOM_H
#include <string>
#include <vector>
#include <set>
#include "strategy.h"
#include <random>


class Random :public Strategy
{
public:
    Random();
    ~Random();
    string decideAttackingCountry(RiskMap map);
};

#endif // RANDOM_H
