#ifndef PLAYER
#define PLAYER

class Player{
private:
    String name;
    Country countriesOwned[];
    Card cards[];
    int newSoldiers;
public:
    Player(String name, Country countriesOwned[]);
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

