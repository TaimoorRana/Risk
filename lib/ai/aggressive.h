#ifndef AI_AGGRESSIVE_H
#define AI_AGGRESSIVE_H
#include "strategy.h"

/**
 * @brief The Aggressive class extends Strategy
 * Implements the Aggressive strategy pattern which attacks
 * as long as one bordering territory has less armies.
 */
class Aggressive : public Strategy
{
public:
	~Aggressive() {}
	std::pair<std::string, std::string> attackPhase();
};

#endif // AI_AGGRESSIVE_H
