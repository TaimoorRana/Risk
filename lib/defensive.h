#ifndef DEFENSIVE_H
#define DEFENSIVE_H
#include "strategy.h"
/**
 * @brief The Defensive class extends the strategy class
 * implements the defensive strategy pattern of only attack when all
 * bordering territories have less armies
 */

class Defensive : public Strategy
{
public:
    /**
     * @brief Defensive
     * Default constructor
     */
    Defensive();
    /**
     * @brief Defensive
     * Default Destructor
     */
    ~Defensive();
    /**
     * @brief decideAttackingCountry
     * @param map general map uses as is does not copy
     * Decides the attacking country based of defensive strategy
     * and then returns it.
     * @return
     */
    string decideAttackingCountry(RiskMap map);
private:

    // needs to have atleast 4 armies
    int twoAdditionalArmies=2;
};

#endif // DEFENSIVE_H
