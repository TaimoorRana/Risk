#ifndef WARREFEREE
#define WARREFEREE
#include "country.h"
#include "player.h"

class WarReferee {
//use singleton pattern
private:
    static const int MAX_DICES = 3;
    // Players
    Player* attacker;
    Player* defender;

    int defenderDices;
    int attackerDices;
    WarReferee();
public:
    static WarReferee& getInstance();
    void setPlayers(Player &attacker, Player &defender);
    void calculateLossesHelper(Country& attacker, int attackerDices, Country& defender, int defenderDices);
    void calculateLosses(Country& attacker, Country& defender);
    void calculateLosses(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void startWar(Player &attacker, Country &attackerCountry, Player &defender, Country &defenderCountry);
    void allInMode(Country& attacker, Country& defenderCountry);
};

#endif // WARREFEREE

