#ifndef AI_DEFENSIVE_H
#define AI_DEFENSIVE_H
#include "strategy.h"

/**
 * @brief The Defensive AI pattern which attacks only attack when all bordering
 * territories have fewer armies
 */
class Defensive : public Strategy
{
public:
	~Defensive() {}
	std::pair<std::string, std::string> attackPhase();
};

#endif // AI_DEFENSIVE_H
