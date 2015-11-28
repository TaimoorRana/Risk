#include "player_log.h"

PlayerLog::PlayerLog(string name)
{
	playerName=name;
}

void PlayerLog::setCurrentPlayer(string s)
{
    playerName = s;
}

void PlayerLog::log()
{
	//cout <<getLog();
}

string PlayerLog::getLog()
{
	return "current player is :" + playerName + " ";
}

