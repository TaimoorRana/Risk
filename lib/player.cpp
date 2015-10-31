#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
    this->name = name;
}

//Player::Player(const Player& other): name(other.name),reinforcements(other.reinforcements),countriesOwned(other.countriesOwned),cards(other.cards){}

void Player::addCountry(std::string countryName)
{
    namesOfCountriesOwned.push_back(countryName);
}

void Player::removeCountry(std::string countryName)
{
    int index = 0;
    for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        index++;
        if(*countryOwnedIterator == countryName){
            namesOfCountriesOwned.erase(countryOwnedIterator);
            break;
        }
    }

}

bool Player::hasCountry(std::string countryName)
{
    for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        if(*countryOwnedIterator == countryName){
            return true;
        }
    }
    return false;
}

std::string Player::getName(){
    return name;
}

void Player::transferSoldiers(Country& countryFrom, Country& countryTo, int soldiers){

}

std::vector<string> Player::getCountryOwned(){
    std::vector<string> copy(namesOfCountriesOwned);
    return copy;
}



