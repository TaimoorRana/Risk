#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "strategy.h"
#include "aggressive.h"
#include "random.h"
#include "player_subject.h"
#include "player_observer.h"
#include "player.h"
#include <string>

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
