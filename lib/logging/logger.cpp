#include "logger.h"

Logger::Logger() {
	this->listeners = std::list<LogListener*>();
}

Logger* Logger::getInstance() {
	static Logger* instance = nullptr;
	if (instance == nullptr) {
		instance = new Logger();
	}
	return instance;
}

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

void Logger::notifyListeners(std::string playerName, Mode mode, std::string message) {
	for (LogListener* listener : listeners) {
		listener->messageLogged(playerName, mode, message);
	}
};

void Logger::attachListener(LogListener* listener) {
	listeners.push_back(listener);
};

void Logger::detachListener(LogListener* listener) {
	listeners.remove(listener);
};
