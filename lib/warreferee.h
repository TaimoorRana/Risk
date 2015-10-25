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
    // used for singleton pattern
    static bool instanceFlag;
    static WarReferee* instance;
    WarReferee();
    
    Dices *dices;
    
    // dices used by the players
    int defenderDices;
    int attackerDices;
    
public:
    static void setPlayers(Player attacker, Player defender);
    static WarReferee* getInstance();
    std::vector<CountryLost*> calculateLossesHelper(Country& attacker, int attackerDices, Country& defender, int defenderDices);
    std::vector<CountryLost*> calculateLosses(Country& attacker, Country& defender);
    std::vector<CountryLost*> calculateLosses(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void removeSoldiers(std::vector<CountryLost *> countriesCasualties);
    void startWar(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void allInMode(Country& attacker, Country& defender);
    
};


#endif // DICESREFEREE

