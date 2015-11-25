#include "computer_player.h"
#include "strategy.h"
#include "random.h"
#include "aggressive.h"
#include <string>



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

void ComputerPlayer::setAttackFrom(string countryName, int numberOfArmies)
{
    strategy->setAttackFrom(countryName,numberOfArmies);



}

void ComputerPlayer::registerObserver(Observable *)
{

}

void ComputerPlayer::unregisterObserver(Observable *)
{

}

void ComputerPlayer::notifyObserver()
{

}





