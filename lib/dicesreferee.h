#ifndef DICESREFEREE
#define DICESREFEREE
#include "country.h"
#include "countrylost.h"
class DicesReferee{

//use singleton pattern
private:
    static const int MAX_DICES = 3;
    int defenderDices;
    int attackerDices;
public:
    DicesReferee();

    std::vector<CountryLost*> calculateLossesHelper(Country& attacker, int attackerDices, Country& defender, int defenderDices);
    std::vector<CountryLost*> calculateLosses(Country& attacker, Country& defender);
    std::vector<CountryLost*> calculateLosses(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void removeSoldiers(std::vector<CountryLost *> countriesCasualties);
    void startWar(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void allInMode(Country& attacker, Country& defender);

};

#endif // DICESREFEREE

