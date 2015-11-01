#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Country; // forward declaration

class Player{
private:

	std::string name;
	int reinforcements;
    std::vector<std::string> namesOfCountriesOwned;
    std::vector<std::string> namesOfContinentsOwned;
    int battleWon;

public:

	Player(std::string name);
    Player(const Player& other);
    std::string getName();

	void rollDices();

    // Reinforcements related methods
    void addReinforcements(int amount);
    void removeReinforcements(int amount);
    void setReinforcements(int amount);

    // country related methods
    void addCountry(std::string);
    void removeCountry(std::string);
    bool hasCountry(std::string);
    std::vector<std::string> getCountryOwned();

    // continent related methods
    void addContinent(std::string);
    void removeContinent(std::string);
    bool hasContinent(std::string);

    // need to request map to do the transfer
	void transferSoldiers(Country& countryFrom, Country& countryTo, int Soldiers);
};

#endif // PLAYER_H
