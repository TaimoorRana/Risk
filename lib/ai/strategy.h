#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H
#include <string>
#include <utility>
#include "country.h"
#include "game_driver.h"
#include "game_modes.h"
#include "risk_map.h"

/**
 * @brief An abstract class which implements the Strategy design pattern to
 * allow for different AIs. Each implementation overrides methods to handle
 * phase actions.
 */
class Strategy
{
public:
	Strategy();
	virtual ~Strategy() {};

	void takeAction(Mode mode);
	virtual std::string reinforcePhase();
	virtual std::pair<std::string, std::string> attackPhase() = 0;
	std::pair<std::string, std::string> fortifyPhase();

protected:
	GameDriver* driver = nullptr;
};

#endif // AI_STRATEGY_H
