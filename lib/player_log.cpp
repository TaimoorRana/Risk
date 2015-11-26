#include "player_log.h"

PlayerLog::PlayerLog()
{

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
    return "current player is :" + playerName;
}

