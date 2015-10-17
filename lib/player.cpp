#include <iostream>
#include <string>
#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
	this->name = name;
}

void Player::addCountry(Country *country)
{
	// TODO implement with vector
	/*
	if(indexOfLastElementInCardsOwned < AMOUNT_OF_COUNTRIES){
		countriesOwned[indexOfLastElementInCountriesOwned] = country;
		indexOfLastElementInCountriesOwned++;
	}
	*/
}

void Player::removeCountry(Country *country)
{
	// TODO implement with vector
	/*
	int indexFoundAt = -1;
	for(int x = 0; x < indexOfLastElementInCountriesOwned; x++){
		if (countriesOwned[x]->getName() == country->getName()){
			indexFoundAt = x;
			break;
		}
	}

	if(indexFoundAt != -1){
	}
	*/
}

