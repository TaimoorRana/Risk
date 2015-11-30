#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <list>
#include "game_modes.h"
#include "log_listener.h"
#include "player.h"

/**
 * @brief Singleton class that can be used throughout the code base to create
 * log messages (message source). Sends events to message listeners.
 */
class Logger {
public:
	~Logger();
	static Logger* getInstance();
	void logMessage(std::string playerName, Mode mode, std::string message);
	void attachListener(LogListener* listener);
	void detachListener(LogListener* listener);
	void notifyListeners(std::string playerName, Mode mode, std::string message);

protected:
	Logger();
	std::list<LogListener*> listeners;
};

#endif // LOGGER_H
