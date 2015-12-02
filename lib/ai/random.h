#ifndef AI_RANDOM_H
#define AI_RANDOM_H
#include "strategy.h"

/**
 * @brief The Random class
 * extends Strategy and implements the random strategy pattern of attacking any bordering country
 * at random
 */
class Random : public Strategy
{
public:
	~Random() {}
	std::pair<std::string, std::string> attackPhase();
};

#endif // AI_RANDOM_H
