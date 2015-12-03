#include "logger.h"

Logger::Logger() {
	this->listeners = std::list<LogListener*>();
}

/**
 * @brief Get the singleton Logger instance, useful for logging a new message
 * or to register a new listener.
 */
Logger* Logger::getInstance() {
	static Logger* instance = nullptr;
	if (instance == nullptr) {
		instance = new Logger();
	}
	return instance;
}

/**
 * @brief Formats a new log message and sends it to all LogListeners
 */
void Logger::logMessage(std::string playerName, Mode mode, std::string message) {
	std::string phase = "Unknown";
	if (mode == REINFORCEMENT) {
		phase = "reinforcement";
	}
	else if (mode == ATTACK) {
		phase = "attack";
	}
	else if (mode == FORTIFICATION) {
		phase = "fortification";
	}

	this->notifyListeners(playerName, mode, playerName + " [" + phase +"]: " + message + "\n");
}

/**
 * @brief Notify all LogListeners about a new message
 */
void Logger::notifyListeners(std::string playerName, Mode mode, std::string message) {
	for (LogListener* listener : listeners) {
		listener->messageLogged(playerName, mode, message);
	}
};

/**
 * @brief Attaches a new LogListener for notifications about new log messages
 */
void Logger::attachListener(LogListener* listener) {
	listeners.push_back(listener);
};

/**
 * @brief Detaches a LogListener from new log message notifications
 */
void Logger::detachListener(LogListener* listener) {
	listeners.remove(listener);
};
