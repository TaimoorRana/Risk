#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H
#include "strategy.h"

class Aggressive : public Strategy
{
public:
    Aggressive();
    ~Aggressive();
    string decideAttackingCountry(RiskMap map);
};

#endif // AGGRESSIVE_H
