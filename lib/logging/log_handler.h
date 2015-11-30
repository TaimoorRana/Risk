#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H
#include <string>

/**
 * @brief Interface for observing classes that will react to a new log message
 * being pushed out from a decorated LogLister message sink.
 */
class LogHandler {
public:
	virtual void messageLogged(std::string message) = 0;
	virtual ~LogHandler(){}
protected:
	LogHandler() {};
};

#endif // LOG_HANDLER_H
