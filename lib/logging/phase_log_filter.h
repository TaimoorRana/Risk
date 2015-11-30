#ifndef PHASE_LOG_FILTER_H
#define PHASE_LOG_FILTER_H
#include <string>
#include "game_modes.h"
#include "log_listener.h"

/**
 * @brief Decorates the LogListener class to filters log messages by game phase.
 */
class PhaseLogFilter : public LogListener {
public:
	/**
	 * @brief PhaseLogFilter
	 * @param pointer to the listener to be decorated
	 * @param GameMode enum value to filter log messages on
	 */
	PhaseLogFilter(LogListener* logger, Mode mode);
	virtual bool filter(std::string playerName, Mode mode);

private:
	Mode mode;
	LogListener* logger;
};

#endif // PHASE_LOG_FILTER_H
