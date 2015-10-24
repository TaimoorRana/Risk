#ifndef DICESREFEREE
#define DICESREFEREE
#include "dices.h"
#include "country.h"
#include "countrylost.h"
class DicesReferee{

//use singleton pattern
private:
    static const int MAX_DICES = 3;
    Dices *dices;
public:
    DicesReferee();
    
    std::vector<CountryLost*> calculateLossesHelper(Country& attacker, int attackerDices, Country& defender, int defenderDices);
    std::vector<CountryLost*> calculateLosses(Country& attacker, Country& defender);
    std::vector<CountryLost*> calculateLosses(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    void removeSoldiers(std::vector<CountryLost *> countriesCasualties);
    void startWar(Country& attacker, int attackerDices,Country& defender, int defenderDices);
    std::vector<CountryLost*> compareDices(std::vector<int> attackerResult, std::vector<int> defenderResult);
    void allInMode(Country& attacker, Country& defender);

};

#endif // DICESREFEREE

