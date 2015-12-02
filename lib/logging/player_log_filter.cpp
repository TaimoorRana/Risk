#include "player_log_filter.h"

PlayerLogFilter::PlayerLogFilter(LogListener* logger, std::string playerName) {
	this->logger = logger;
	this->playerName = playerName;
}

/**
 * @brief Decorated method to filters log messages sent from the Logger message
 * source. Filters by player name.
 */
bool PlayerLogFilter::filter(std::string playerName, Mode mode) {
	return playerName == this->playerName || this->logger->filter(playerName, mode);
}
