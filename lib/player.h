#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>
#include "player_subject.h"
#include "player_observer.h"
class Country; // forward declaration

class Player: public PlayerSubject{
private:
	int reinforcements = 0;
	int battleWon = 0;
	int totalArmy = 0;
	std::string name = "";
	std::set<std::string> namesOfCountriesOwned;
	std::set<std::string> namesOfContinentsOwned;
    std::set<PlayerObserver*> observerList;

public:
	Player() {}
	Player(std::string name);
    //Player(const Player& other);
	std::string getName() const;

	// increase battleWon int by 1
	void increaseBattleWon();
	void decreaseBattleWon();
	void setBattlesWon(const int &battleWon);
    int getBattlesWon() const;

	/*
	 Reinforcements related methods
	 @params int: number of soldiers
	 */
	void addReinforcements(const int&);
	void removeReinforcements(const int&);
	void setReinforcements(const int&);
	int getReinforcements() const;

	/*
	 Country related methods
	 @params string: countries name
	 */
	void addCountry(const std::string&);
	void removeCountry(const std::string&);
	bool hasCountry(const std::string&) const;
	std::set<std::string> getCountryOwned();

	/*
	 continent related methods
	 @params string: continents name
	*/
	void addContinent(const std::string&);
	void removeContinent(const std::string&);
	bool hasContinent(const std::string&) const;
	std::set<std::string> getContinentsOwned() const;


	/*
	 * Observer Pattern Methods
	 */
	virtual void registerObserver(PlayerObserver*);
	virtual void unregisterObserver(PlayerObserver*);
	virtual void notifyObserver();

	/*
	 * Army Related Methods
	 */
	int getTotalArmy() const;
    void setTotalArmy(const int& totalArmy);
};
#endif // PLAYER_H
