#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "strategy.h"
#include "aggressive.h"
#include "random.h"
#include "observer.h"
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
    /*
     * Observer Pattern Methods
     */
	virtual void registerObserver(Observable*);
	virtual void unregisterObserver(Observable *);
    virtual void notifyObserver();
private:
    Strategy* strategy;
};

#endif // COMPUTER_PLAYER_H
