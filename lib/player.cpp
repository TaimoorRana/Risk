#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
    this->name = name;
}


void Player::addCountry(std::string countryName)
{
    namesOfCountriesOwned.push_back(countryName);
}

void Player::addContinent(std::string continentName)
{
    namesOfContinentsOwned.push_back(continentName);
}


void Player::removeCountry(std::string countryName)
{
    std::vector<std::string>::iterator countryOwnedIterator;
    int index = 0;
    for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        index++;
        if(*countryOwnedIterator == countryName){
            namesOfCountriesOwned.erase(countryOwnedIterator);
            break;
        }
    }

}

void Player::removeContinent(std::string continentName)
{
    std::vector<std::string>::iterator continentsOwnedIterator;
    int index = 0;
    for(continentsOwnedIterator = namesOfContinentsOwned.begin(); continentsOwnedIterator != namesOfContinentsOwned.end(); continentsOwnedIterator++){
        index++;
        if(*continentsOwnedIterator == continentName){
            namesOfContinentsOwned.erase(continentsOwnedIterator);
            break;
        }
    }

}

bool Player::hasCountry(std::string countryName)
{
     std::vector<std::string>::iterator countryOwnedIterator;
     for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        if(*countryOwnedIterator == countryName){
            return true;
        }
    }
    return false;
}

bool Player::hasContinent(std::string continentName)
{
     std::vector<std::string>::iterator continentsOwnedIterator;
     for(continentsOwnedIterator = namesOfContinentsOwned.begin(); continentsOwnedIterator != namesOfContinentsOwned.end();continentsOwnedIterator++){
        if(*continentsOwnedIterator == continentName){
            return true;
        }
    }
    return false;
}

std::string Player::getName(){
    return name;
}

void Player::addReinforcements(int amount)
{
    reinforcements += amount;
}

void Player::removeReinforcements(int amount)
{
    if(reinforcements - amount >= 0 ){
        reinforcements -= amount;
    }
}

void Player::setReinforcements(int amount)
{
    reinforcements = amount;
}

void Player::transferSoldiers(Country& countryFrom, Country& countryTo, int soldiers){

}

std::vector<std::string> Player::getCountryOwned(){
    std::vector<std::string> copy(namesOfCountriesOwned);
    return copy;
}



