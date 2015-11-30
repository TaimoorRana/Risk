#include "log_listener.h"
#include "logger.h"
#include "debug.h"

LogListener::LogListener() {
	handlers = std::list<LogHandler*>();
}

LogListener::~LogListener() {}

void LogListener::messageLogged(std::string playerName, Mode mode, std::string message) {
	if (this->filter(playerName, mode)) {
		this->notifyHandlers(message);
	}
}

void LogListener::notifyHandlers(std::string message) {
	for (LogHandler* handler : handlers) {
		handler->messageLogged(message);
	}
};

bool LogListener::filter(std::string playerName, Mode mode) {
	return false;
}

void LogListener::attachHandler(LogHandler* handler) {
	handlers.push_back(handler);
};

void LogListener::detachHandler(LogHandler* handler) {
	handlers.remove(handler);
};
