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
	/**
	 * @brief getName
	 * @return name of the player
	 */
	std::string getName() const;

	/**
	 * @brief increaseBattleWon increases battleWon value by 1
	 */
	void increaseBattleWon();

	/**
	 * @brief decreaseBattleWon decreases battleWon value by 1
	 */
	void decreaseBattleWon();

	/**
	 * @brief setBattlesWon sets battleWon value
	 * @param battleWon
	 */
	void setBattlesWon(const int &battleWon);

	/**
	 * @brief getBattlesWon
	 * @return total battles won
	 */
    int getBattlesWon() const;


	/**
	 * @brief addReinforcements
	 * @param amount
	 */
	void addReinforcements(const int& amount);

	/**
	 * @brief removeReinforcements
	 * @param amount
	 */
	void removeReinforcements(const int& amount);

	/**
	 * @brief setReinforcements
	 * @param amount
	 */
	void setReinforcements(const int& amount);

	/**
	 * @brief getReinforcements
	 * @return total reinforcements
	 */
	int getReinforcements() const;


	/**
	 * @brief addCountry
	 * @param name
	 */
	void addCountry(const std::string& name);

	/**
	 * @brief removeCountry
	 * @param name
	 */
	void removeCountry(const std::string& name);
	/**
	 * @brief hasCountry checks if the country belongs to the player
	 * @param name
	 * @return true if found
	 */
	bool hasCountry(const std::string& name) const;

	/**
	 * @brief getCountryOwned
	 * @return a set of countries owned
	 */
	std::set<std::string> getCountryOwned();

	/**
	 * @brief addContinent
	 * @param name
	 */
	void addContinent(const std::string& name);
	/**
	 * @brief removeContinent
	 * @param name
	 */
	void removeContinent(const std::string& name);

	/**
	 * @brief hasContinent checks if the continent belongs to the player
	 * @param name
	 * @return true if found
	 */
	bool hasContinent(const std::string& name) const;

	/**
	 * @brief getContinentsOwned
	 * @return a set of continents owned
	 */
	std::set<std::string> getContinentsOwned() const;


	/**
	 * @brief registerObserver
	 * @param observer
	 */
	virtual void registerObserver(PlayerObserver* observer);

	/**
	 * @brief unregisterObserver
	 * @param observer
	 */
	virtual void unregisterObserver(PlayerObserver* observer);

	/**
	 * @brief notifyObserver notify all the observers to update
	 */
	virtual void notifyObserver();

	/**
	 * @brief getTotalArmy
	 * @return total number of army
	 */
	int getTotalArmy() const;

	/**
	 * @brief setTotalArmy
	 * @param totalArmy
	 */
    void setTotalArmy(const int& totalArmy);
};
#endif // PLAYER_H
