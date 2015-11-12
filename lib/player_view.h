#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <string>
#include <set>
#include "observer.h"
#include "player.h"
class PlayerView: public Observer {
private:
	std::set<std::string> countriesOwned;
	std::set<std::string> continentsOwned;
	int nbrOfReinforcements;
	int nbrOfArmies;
	int nbrBattleWon;
	std::string name;
	Player* player;

public:
	PlayerView(Player* player);
	~PlayerView();
	void observedUpdated();
	std::string getName() const;
	std::set<std::string> getCountriesOwned() const;
	std::set<std::string> getContinentsOwned() const;
	int getNumberOfReinforcements() const;
	int getNumberOfArmies() const;
	int getNumberOfBattleWon() const;
};

#endif // PLAYERVIEW_H

