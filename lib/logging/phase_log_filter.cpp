#include "phase_log_filter.h"

PhaseLogFilter::PhaseLogFilter(LogListener* logger, Mode mode) {
	this->logger = logger;
	this->mode = mode;
}

/**
 * @brief Decorated method to filters log messages sent from the Logger message
 * source. Filters by game phase (i.e. mode).
 */
bool PhaseLogFilter::filter(std::string playerName, Mode mode) {
	return mode == this->mode || this->logger->filter(playerName, mode);
}
