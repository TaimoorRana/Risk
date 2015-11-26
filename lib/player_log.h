#ifndef PLAYERLOG_H
#define PLAYERLOG_H
#include "component.h"
#include <string>

using namespace std;
/**
 * @brief The PlayerLog class which extends Component and will be used to be decorated
 */
class PlayerLog : public Component
{
public:
	/**
	 * @brief PlayerLog
	 * @param s
	 */
	PlayerLog(string s);
	/**
	 * @brief setCurrentPlayer
	 * @param s
	 */
    void setCurrentPlayer(string s);
    void log();
    string getLog();
private:
    string playerName;
	//string logString;
};

#endif // PLAYERLOG_H
