#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include <string>

#include "ai/strategy.h"
#include "player.h"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    ComputerPlayer(std::string name);
    void setStrategy(Strategy *strategyP);
    void setAttackFrom(std::string countryName, int numberOfArmies);
    Strategy* getStrategy();
private:
    Strategy* strategy;
};

#endif // COMPUTER_PLAYER_H
