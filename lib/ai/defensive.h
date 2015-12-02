#ifndef AI_DEFENSIVE_H
#define AI_DEFENSIVE_H
#include "strategy.h"

/**
 * @brief The Defensive class extends the strategy class
 * implements the defensive strategy pattern of only attack when all
 * bordering territories have less armies
 */
class Defensive : public Strategy
{
public:
	~Defensive() {}
	std::pair<std::string, std::string> attackPhase();
};

#endif // AI_DEFENSIVE_H
