#ifndef COMPONENT_H
#define COMPONENT_H


#include <string>
using namespace std;
/**
 * @brief The Component class
 * the abstract class to allow us to implement the decorator pattern
 * contains the log and getLog() functions for logging.
 *
 */
class Component {
public:
	virtual ~Component() {};
	/**
	 * @brief log
	 * the log of string to display which in subclasses combines with the string of other Component
	 * thereby using the decorator pattern
	 */
	virtual void log()=0;
	//virtual void setLog(string s)=0;
	/**
	 * @brief getLog returns the log as a string of the occurences
	 * @return
	 */
	virtual string getLog()=0;
	//virtual void setCurrentPlayer(string s)=0;
protected:
	string logString;
};

#endif // COMPONENT_H
