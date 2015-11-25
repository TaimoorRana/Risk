#ifndef RANDOM_H
#define RANDOM_H
#include <string>
#include <vector>
#include <set>
#include "strategy.h"
#include <random>

/**
 * @brief The Random class
 * extends Strategy and implements the random strategy pattern of attacking any bordering country
 * at random
 */
class Random :public Strategy
{
public:
    /**
     * @brief Random
     * Default constructor
     */
    Random();
    /**
     * @brief Random
     * Default Destructor
     */
    ~Random();
    /**
     * @brief decideAttackingCountry
     * @param map - the current game map
     * Ovewrites parent method and decides using the defensive strategy which country to attack
     * @return
     */
    string decideAttackingCountry(RiskMap map);
};

#endif // RANDOM_H
