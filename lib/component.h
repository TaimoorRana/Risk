#ifndef COMPONENT
#define COMPONENT


#include <string>
using namespace std;
/**
 * @brief The Component class
 * the abstract class to implement the decorator pattern
 * this is the parent of decorator
 */
class Component {
public:
	/**
	 * @brief log
	 * the log of string to display which in subclasses combines with the string of other Component
	 */
	virtual void log()=0;
	//virtual void setLog(string s)=0;
	/**
	 * @brief getLog returns the log as a string
	 * @return
	 */
	virtual string getLog()=0;
	//virtual void setCurrentPlayer(string s)=0;
protected:
	string logString;
};

#endif // COMPONENT


