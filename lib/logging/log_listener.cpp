#include "log_listener.h"
#include "logger.h"
#include "debug.h"

LogListener::LogListener() {
	handlers = std::list<LogHandler*>();
}

LogListener::~LogListener() {}

/**
 * @brief Processes a newly logged message from the Logger instance, applying
 * any decorated filters.
 */
void LogListener::messageLogged(std::string playerName, Mode mode, std::string message) {
	if (this->filter(playerName, mode)) {
		this->notifyHandlers(message);
	}
}

/**
 * @brief Notifies any attached handlers about a new message (but only if it
 * passed filtering).
 */
void LogListener::notifyHandlers(std::string message) {
	for (LogHandler* handler : handlers) {
		handler->messageLogged(message);
	}
};

/**
 * @brief Decorated method to filters log messages sent from the Logger message
 * source
 */
bool LogListener::filter(std::string playerName, Mode mode) {
	return false;
}

/**
 * @brief Attaches a log handler to listen for passing log messages
 */
void LogListener::attachHandler(LogHandler* handler) {
	handlers.push_back(handler);
};

/**
 * @brief Detaches a listening log handler
 */
void LogListener::detachHandler(LogHandler* handler) {
	handlers.remove(handler);
};
