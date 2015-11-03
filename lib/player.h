#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "card.h"

class Country; // forward declaration

class Player{
private:
	std::string name;
	int reinforcements;
	std::vector<Country> countriesOwned;
	std::vector<Card> cards;
public:
	Player(std::string name);
	std::string getName() const;
	void setName(const std::string& name);
	void addCountry(Country *country);
	void removeCountry(Country *country);
};

#endif // PLAYER_H
