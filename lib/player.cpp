#include <iostream>
#include <string>
#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
	this->name = name;
}

//Player::Player(const Player& other): name(other.name),reinforcements(other.reinforcements),countriesOwned(other.countriesOwned),cards(other.cards){}

void Player::addCountry(Country& country)
{
    // TODO implement with vector
    countriesOwned.push_back(&country);
    country.setOwner(this);
}

//void Player::removeCountry(Country& country)
//{
//	// TODO implement with vector
//    countriesOwned.erase(std::remove(countriesOwned.begin(),countriesOwned.end(),country));
//}

Country* Player::findCountry(std::string countryName)
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

void Player::transferSoldiers(Country& countryFrom, Country& countryTo, int soldiers){
    if (soldiers < countryFrom.getSoldiers() && countryFrom.getOwner()->getName() == countryTo.getOwner()->getName()) {
        countryFrom.adjustSoldiers(-soldiers);
        countryTo.adjustSoldiers(soldiers);
    }
}

std::vector<Country> Player::getCountryOwned(){
    std::vector<Country> listCopy;
    for (int x = 0; x < countriesOwned.size(); x++) {
        listCopy.push_back(*countriesOwned[x]);
    }
    return listCopy;
}



