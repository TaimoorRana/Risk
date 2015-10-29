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
}

Country* Player::findCountry(std::string countryName)
{

}

std::string Player::getName(){
    return name;
}

void Player::transferSoldiers(Country& countryFrom, Country& countryTo, int soldiers){

}

std::vector<Country> Player::getCountryOwned(){

}



