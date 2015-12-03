#ifndef AI_AGGRESSIVE_H
#define AI_AGGRESSIVE_H
#include "strategy.h"

/**
 * @brief Aggressive AI pattern which attacks as long as one bordering territory
 * has fewer armies
 */
class Aggressive : public Strategy
{
public:
	~Aggressive() {}
	std::pair<std::string, std::string> attackPhase();
};

#endif // AI_AGGRESSIVE_H
