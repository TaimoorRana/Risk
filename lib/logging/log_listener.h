#ifndef LOG_LISTENER_H
#define LOG_LISTENER_H
#include <list>
#include <string>
#include "log_handler.h"
#include "game_modes.h"

/**
 * @brief Listener (message sink) connected to the Logger singleton (message
 * source) that implements the Decorator pattern to dynamically filter observed
 * log messages. This is the base class for the filter decorators.
 */
class LogListener {
public:
	LogListener();
	virtual ~LogListener();
	void messageLogged(std::string playerName, Mode mode, std::string message);
	virtual bool filter(std::string playerName, Mode mode);
	void attachHandler(LogHandler* handler);
	void detachHandler(LogHandler* handler);
	void notifyHandlers(std::string message);
protected:
	std::list<LogHandler*> handlers;
};

#endif // LOG_LISTENER_H
