#ifndef PLAYER_LOG_FILTER_H
#define PLAYER_LOG_FILTER_H
#include <string>
#include "game_modes.h"
#include "log_listener.h"

/**
 * @brief Decorates the LogListener class to filter log messages by player
 */
class PlayerLogFilter : public LogListener {
public:
	/**
	 * @brief PlayerLogFilter
	 * @param pointer to the listener to be decorated
	 * @param player name string to filter log messages on
	 */
	PlayerLogFilter(LogListener* logger, std::string playerName);
	virtual bool filter(std::string playerName, Mode mode);

private:
	std::string playerName;
	LogListener* logger;
};

#endif // PLAYER_LOG_FILTER_H
