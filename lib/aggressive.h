#ifndef AGGRESSIVE_H
#define AGGRESSIVE_H
#include "strategy.h"
/**
 * @brief The Aggressive class extends Strategy
 * Implements the Aggressive strategy pattern which attacks
 * as long as one bordering territory has less armies.
 */

class Aggressive : public Strategy
{
public:
    Aggressive();
    ~Aggressive();
    /**
     * @brief decideAttackingCountry
     * @param map - the current map state of the game
     * Ovewrites parent method and decides using the aggressive strategy which country to attack
     * @return
     */
    string decideAttackingCountry(RiskMap map);
};

#endif // AGGRESSIVE_H
