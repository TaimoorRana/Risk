#ifndef DICESREFEREE
#define DICESREFEREE
#include "dices.h"
#include "country.h"
#include "countrylost.h"
#include "player.h"
class WarReferee{

//use singleton pattern
private:
    
    static const int MAX_DICES = 3;
    
    // Players
    Player* attacker;
    Player* defender;
    
    
    // dices used by the players
    Dices *dices;
    int defenderDices;
    int attackerDices;
    
public:
    WarReferee();
    ~WarReferee();
    void setPlayers(Player &attacker, Player &defender);
    void calculateLossesHelper(Country& attacker, int attackerDices, Country& defender, int defenderDices);
    void calculateLosses(Country& attacker, Country& defender);
    void calculateLosses(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void removeSoldiers(std::vector<CountryLost *> countriesCasualties);
    void startWar(Player &attacker, Country &attackerCountry, Player &defender, Country &defenderCountry);
    void allInMode(Country& attacker, Country& defenderCountry);
    
};


#endif // DICESREFEREE

