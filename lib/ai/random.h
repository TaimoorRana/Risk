#ifndef AI_RANDOM_H
#define AI_RANDOM_H
#include <string>

#include "strategy.h"

/**
 * @brief The Random class
 * extends Strategy and implements the random strategy pattern of attacking any bordering country
 * at random
 */
class Random : public Strategy
{
public:
	/**
	 * @brief decideAttackingCountry
	 * @param map - the current game map
	 * Ovewrites parent method and decides using the defensive strategy which country to attack
	 * @return
	 */
	std::string decideAttackingCountry(RiskMap map);
};

#endif // AI_RANDOM_H
