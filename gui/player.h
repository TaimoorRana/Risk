//#include "country.h"
#ifndef PLAYER
#define PLAYER
#include "card.h"
#include <string>
class Country;
class Player{
private:
    const static int AMOUNT_OF_COUNTRIES = 40;
    int indexOfLastElementInCountriesOwned = 0;
    int indexOfLastElementInCardsOwned = 0;
    std::string name;
    Country *countriesOwned[AMOUNT_OF_COUNTRIES];
    Card *cardsOwned[AMOUNT_OF_COUNTRIES];
    int newSoldiers;
public:
    Player(std::string name);
    void rollDices();

    void addCountry(Country *country);
    void removeCountry(Country *country);
    void printCountries();

    void addCard(Card card);
    void removeCard(Card card);

    void addNewSoldiers();
    void removeNewSoldiers();

    void transferSoldiers(Country countryFrom, Country countryTo, int Soldiers);

    void attackCountry(Country country);
};

#endif // PLAYER

