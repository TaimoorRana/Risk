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
    std::vector<CountryLost*> calculateLosses(Country *attacker, int attackerDices,Country *defender, int defenderDices);
    void adjustSoldiers(std::vector<CountryLost *> countriesCasualties);
    void startWar(Country *attacker, int attackerDices,Country *defender, int defenderDices);
    std::vector<int> rollAndSaveDices(int amountOfDices);
    //static DicesReferee *getInstance();

};

#endif // DICESREFEREE

