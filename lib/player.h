#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "card.h"

class Country; // forward declaration

class Player{
private:
	std::string name;
	int reinforcements;
    std::vector<Country*> countriesOwned;
	std::vector<Card> cards;
public:
	Player(std::string name);
    Player(const Player& other);
	void rollDices();

	void addCountry(Country *country);
	void removeCountry(Country *country);
    Country* findCountry(std::string countryName);

	void addCard(Card card);
	void removeCard(Card card);
    
    std::string getName();
    
	void addNewSoldiers();
	void removeNewSoldiers();

	void transferSoldiers(Country countryFrom, Country countryTo, int Soldiers);

	void attackCountry(Country country);
};

#endif // PLAYER_H
