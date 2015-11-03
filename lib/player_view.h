#ifndef PLAYERVIEW
#define PLAYERVIEW
#include "player_observer.h"
#include <string>
#include <set>
class PlayerView: public PlayerObserver{
private:
	std::set<std::string> countriesOwned;
	std::set<std::string> continentsOwned;
	int nbrOfReinforcements;
	int nbrOfArmies;
	int nbrBattleWon;

public:
	void update (std::set<std::string>,std::set<std::string>,int,int,int);
	std::set<std::string> getCountriesOwned() const;
	std::set<std::string> getContinentsOwned() const;
	int getNumberOfReinforcements() const;
	int getNumberOfArmies() const;
	int getNumberOfBattleWon() const;
};

#endif // PLAYERVIEW

