#include "player_log.h"

PlayerLog::PlayerLog(string s)
{
	playerName=s;
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
	return "<b>current player is :" + playerName + "<b>";
}

