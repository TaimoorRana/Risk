#include "computer_player.h"
#include "ai/random.h"

ComputerPlayer::ComputerPlayer():Player()
{
    strategy = new Random();
}
ComputerPlayer::ComputerPlayer(std::string name):Player(name)
{
    strategy = new Random();
}

void ComputerPlayer::setStrategy(Strategy* strategyP)
{
    this->strategy = strategyP;
}

void ComputerPlayer::setAttackFrom(std::string countryName, int numberOfArmies)
{
    strategy->setAttackFrom(countryName,numberOfArmies);
}
