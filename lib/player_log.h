#ifndef PLAYERLOG_H
#define PLAYERLOG_H
#include "component.h"
#include <string>

using namespace std;

class PlayerLog : public Component
{
public:
    PlayerLog();
    void setCurrentPlayer(string s);
    void log();
    string getLog();
private:
    string playerName;
    string logString;
};

#endif // PLAYERLOG_H
