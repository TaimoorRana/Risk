#include "player_log_filter.h"

PlayerLogFilter::PlayerLogFilter(LogListener* logger, std::string playerName) {
	this->logger = logger;
	this->playerName = playerName;
}

bool PlayerLogFilter::filter(std::string playerName, Mode mode) {
	return playerName == this->playerName || this->logger->filter(playerName, mode);
}
