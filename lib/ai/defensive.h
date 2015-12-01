#ifndef AI_DEFENSIVE_H
#define AI_DEFENSIVE_H
#include <string>

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
	 * @brief decideAttackingCountry
	 * @param map general map uses as is does not copy
	 * Decides the attacking country based of defensive strategy
	 * and then returns it.
	 * @return
	 */
	std::string decideAttackingCountry(RiskMap *map);
	virtual void whereToAttackFrom(RiskMap *map);


private:
	// needs to have atleast 4 armies
	int twoAdditionalArmies=2;
};

#endif // AI_DEFENSIVE_H
