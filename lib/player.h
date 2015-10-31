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
    
	void addNewSoldiers();
	void removeNewSoldiers();
    std::vector<string> getCountryOwned();

	void transferSoldiers(Country& countryFrom, Country& countryTo, int Soldiers);

	void attackCountry(Country country);
};

#endif // PLAYER_H
