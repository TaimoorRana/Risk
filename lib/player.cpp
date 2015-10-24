#include <iostream>
#include <string>
#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
	this->name = name;
}

Player::Player(const Player& other): name(other.name),reinforcements(other.reinforcements),cards(other.cards),countriesOwned(other.countriesOwned){}

void Player::addCountry(Country *country)
{
    // TODO implement with vector
    countriesOwned.push_back(country);
}

void Player::removeCountry(Country *country)
{
	// TODO implement with vector
    countriesOwned.erase(std::remove(countriesOwned.begin(),countriesOwned.end(),country));
}

Country * Player::findCountry(std::string countryName)
{
    for(int x = 0; x < countriesOwned.size(); x++){
        if(countriesOwned[x]->getName() == countryName){
            return countriesOwned[x];
        }
    }

    // if Country is not found
    return NULL;
}

std::string Player::getName(){
    return name;
}



