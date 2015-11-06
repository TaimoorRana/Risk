#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.h"
#include "strategy.h"
#include <string>

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    ComputerPlayer(std::string name);
    void setStrategy(Strategy *strategy);
    void setAttackFrom(std::string countryName, int numberOfArmies);
    Strategy* getStrategy();
private:
    Strategy* strategy;
};

#endif // COMPUTER_PLAYER_H
