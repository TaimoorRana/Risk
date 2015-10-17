#include <string>
#include "player.h"
#include "country.h"
#include "iostream"
using namespace std;

Player::Player(std::string name)
{
    this->name = name;
}

void Player::addCountry(Country *country)
{
    if(indexOfLastElementInCardsOwned < AMOUNT_OF_COUNTRIES){
        countriesOwned[indexOfLastElementInCountriesOwned] = country;
        indexOfLastElementInCountriesOwned++;
    }
}

void Player::removeCountry(Country *country)
{
    int indexFoundAt = -1;
    for(int x = 0; x < indexOfLastElementInCountriesOwned; x++){
        if (countriesOwned[x]->getName() == country->getName()){
            indexFoundAt = x;
            break;
        }
    }

    if(indexFoundAt != -1){
    }
}

void Player::printCountries()
{
    for(int x = 0; x < indexOfLastElementInCountriesOwned; x++){
        cout << countriesOwned[x]->getName() << endl;
    }
}


