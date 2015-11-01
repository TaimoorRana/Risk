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
    RiskMap& map = RiskMap::getInstance();
    int battleWon;

public:

	Player(std::string name);
    Player(const Player& other);
    std::string getName();
    
    
	void rollDices();
    
    // increase battleWon int by 1
    void increaseBattleWon();

    /*
     Reinforcements related methods
     @params int: number of soldiers
     */
    void addReinforcements(const int&);
    void removeReinforcements(const int&);
    void setReinforcements(const int&);

    /*
     Country related methods
     @params string: countries name
     */
    void addCountry(const std::string&);
    void removeCountry(const std::string&);
    bool hasCountry(const std::string&);
    std::set<std::string> getCountryOwned();

    /*
     continent related methods
     @params string: continents name
    */
    void addContinent(const std::string&);
    void removeContinent(const std::string&);
    bool hasContinent(const std::string&);

    /*
     @params string: Country Name - Transfer from
     @params string: Country Name - Transfer to
     @params int: soldiers to transfer
     */
	void transferSoldiers(std::string&, std::string& ,const int&);
};
#endif // PLAYER_H
