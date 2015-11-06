#ifndef DEFENSIVE_H
#define DEFENSIVE_H
#include "strategy.h"

class Defensive : public Strategy
{
public:
    Defensive();
    ~Defensive();
    string decideAttackingCountry(RiskMap map);
private:
    //1.5 to 1
    double enemyRatio;
    // needs to have atleast 4 armies
    int minimumArmies;
};

#endif // DEFENSIVE_H
