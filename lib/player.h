#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>
#include "risk_map.h"

class Country; // forward declaration

class Player{
private:

	std::string name;
	int reinforcements;
    std::set<std::string> namesOfCountriesOwned;
    std::set<std::string> namesOfContinentsOwned;
    RiskMap map = RiskMap::getInstance();
    int battleWon;

public:

	Player(std::string name);
    Player(const Player& other);
    std::string getName();

	void rollDices();

    // Reinforcements related methods
    void addReinforcements(int);
    void removeReinforcements(int);
    void setReinforcements(int);

    // country related methods
    void addCountry(std::string);
    void removeCountry(std::string);
    bool hasCountry(std::string);
    std::set<std::string> getCountryOwned();

    // continent related methods
    void addContinent(std::string);
    void removeContinent(std::string);
    bool hasContinent(std::string);

    // need to request map to do the transfer
	void transferSoldiers(Country& countryFrom, Country& countryTo, int Soldiers);
};

#endif // PLAYER_H
