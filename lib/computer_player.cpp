#include "computer_player.h"
#include "strategy.h"
#include "random.h"
#include <string>



ComputerPlayer::ComputerPlayer():Player()
{
        strategy = new Random();
}
ComputerPlayer::ComputerPlayer(std::string name):Player(name)
{
        strategy = new Random();
}

void ComputerPlayer::setStrategy(Strategy *strategy)
{
 this->strategy = strategy;
}

void ComputerPlayer::setAttackFrom(string countryName, int numberOfArmies)
{
    strategy->setAttackFrom(countryName,numberOfArmies);

}

