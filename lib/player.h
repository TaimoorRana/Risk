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
    std::vector<std::string>::iterator countryOwnedIterator;
public:
	Player(std::string name);
    Player(const Player& other);
	void rollDices();

    void addCountry(std::string);
    void removeCountry(std::string);
    bool hasCountry(std::string);

    
    std::string getName();

    std::vector<std::string> getCountryOwned();

    // need to request map to do the transfer
	void transferSoldiers(Country& countryFrom, Country& countryTo, int Soldiers);

};

#endif // PLAYER_H
