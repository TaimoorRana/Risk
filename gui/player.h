#include "country.h"
#include "card.h"
#include <string>
#ifndef PLAYER
#define PLAYER
class Player{
private:
    std::string name;
    Country countriesOwned[5];
    Card cards[10];
    int newSoldiers;
public:
    Player(std::string name, Country *countriesOwned);
    void rollDices();

    void addCountry(Country country);
    void removeCountry(Country country);

    void addCard(Card card);
    void removeCard(Card card);

    void addNewSoldiers();
    void removeNewSoldiers();

    void transferSoldiers(Country countryFrom, Country countryTo, int Soldiers);

    void attackCountry(Country country);
};

#endif // PLAYER

