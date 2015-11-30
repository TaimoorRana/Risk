#include "phase_log_filter.h"
#include "debug.h"

PhaseLogFilter::PhaseLogFilter(LogListener* logger, Mode mode) {
	this->logger = logger;
	this->mode = mode;
}

bool PhaseLogFilter::filter(std::string playerName, Mode mode) {
	debug("phase filter queried");
	return mode == this->mode || this->logger->filter(playerName, mode);
}
