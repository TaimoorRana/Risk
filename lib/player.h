#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Country; // forward declaration

class Player{
private:
	std::string name;
	int reinforcements;
    std::vector<Country*> countriesOwned;
public:
	Player(std::string name);
    //Player(const Player& other);
	void rollDices();

	void addCountry(Country& country);
	void removeCountry(Country& country);
    Country* findCountry(std::string countryName);

    
    std::string getName();
    
	void addNewSoldiers();
	void removeNewSoldiers();
    std::vector<Country> getCountryOwned();

	void transferSoldiers(Country& countryFrom, Country& countryTo, int Soldiers);

	void attackCountry(Country country);
};

#endif // PLAYER_H
