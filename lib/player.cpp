#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
    this->name = name;
    map = RiskMap::getInstance();
}


void Player::addCountry(std::string countryName)
{
    namesOfCountriesOwned.insert(countryName);
    map.getCountryObj(countryName)->setPlayer(name);
}


void Player::removeCountry(std::string countryName)
{
    std::set<std::string>::iterator countryOwnedIterator;
    int index = 0;
    for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        index++;
        if(*countryOwnedIterator == countryName){
            namesOfCountriesOwned.erase(countryOwnedIterator);
            break;
        }
    }
    map.getCountryObj(countryName)->setPlayer("");
}

bool Player::hasCountry(std::string countryName)
{
     std::set<std::string>::iterator countryOwnedIterator;
     for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
        if(*countryOwnedIterator == countryName){
            return true;
        }
    }
    return false;
}

bool Player::hasContinent(std::string continentName)
{
    std::set<std::string> countryList = map.listCountriesInsideContinent(continentName);
    std::set<std::string>::iterator countryListIterator;
    
    std::set<std::string>::iterator countriesOwnedIterator;
    int matchFound=0;
    
    for (countryListIterator = countryList.begin(); countryListIterator != countryList.end(); countryListIterator++) {
        for (countriesOwnedIterator = namesOfCountriesOwned.begin(); countriesOwnedIterator != namesOfCountriesOwned.end(); countriesOwnedIterator++) {
            if (countryListIterator == countriesOwnedIterator ) {
                matchFound++;
            }
        }
    }
    
    if (matchFound == countryList.size()) {
        return true;
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

void Player::transferSoldiers(std::string& countryFromName, std::string& countryToName,const int& soldiers){
    Country* countryfrom = map.getCountryObj(countryFromName);
    Country* countryTo = map.getCountryObj(countryToName);
    
    if (countryfrom->getPlayer() == this->name && countryTo->getPlayer() == this->name) {
        countryfrom->removeArmies(soldiers);
        countryTo->addArmies(soldiers);
    }
}

std::set<std::string> Player::getCountryOwned(){
    std::set<std::string> copy(namesOfCountriesOwned);
    return copy;
}



