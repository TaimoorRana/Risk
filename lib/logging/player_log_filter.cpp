#include "player_log_filter.h"
#include "debug.h"

PlayerLogFilter::PlayerLogFilter(LogListener* logger, std::string playerName) {
	this->logger = logger;
	this->playerName = playerName;
}

bool PlayerLogFilter::filter(std::string playerName, Mode mode) {
	debug("player filter queried");
	return playerName == this->playerName || this->logger->filter(playerName, mode);
}
