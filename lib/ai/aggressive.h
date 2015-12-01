#ifndef AI_AGGRESSIVE_H
#define AI_AGGRESSIVE_H
#include <string>

#include "strategy.h"

/**
 * @brief The Aggressive class extends Strategy
 * Implements the Aggressive strategy pattern which attacks
 * as long as one bordering territory has less armies.
 */

class Aggressive : public Strategy
{
public:
	/**
	 * @brief decideAttackingCountry
	 * @param map - the current map state of the game
	 * Ovewrites parent method and decides using the aggressive strategy which country to attack
	 * @return
	 */
	std::string decideAttackingCountry(RiskMap *map);
	virtual void whereToAttackFrom(RiskMap *map);
};

#endif // AI_AGGRESSIVE_H
