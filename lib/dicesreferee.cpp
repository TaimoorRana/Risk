#include "dicesreferee.h"
DicesReferee::DicesReferee(){}

std::vector<CountryLost*> DicesReferee::calculateLosses(Country *attacker, int attackerDices, Country *defender, int defenderDices)
{
    std::vector<int> *ptrDices = dices->roll();
    std::vector<int> attackerResults;
    for(int x = 0; x < attackerDices; x++){
        attackerResults.push_back(ptrDices->at(x));
    }

    ptrDices = dices->roll();
    std::vector<int> defenderResults;
    for(int x = 0; x < attackerDices; x++){
        defenderResults.push_back(ptrDices->at(x));
    }

    int attackerLosses = 0;
    int defenderLosses = 0;

    for(int x = 0; x < defenderDices; x++){
        if(attackerResults[x] > defenderResults[x]){
            defenderLosses++;
        }else{
            attackerLosses++;
        }
    }
    CountryLost *attackerLostResult = new CountryLost(attacker,attackerLosses);
    CountryLost *defenderLostResult = new CountryLost(defender,defenderLosses);
    std::vector<CountryLost*> casualtyResults;
    casualtyResults.push_back(attackerLostResult);
    casualtyResults.push_back(defenderLostResult);
    return casualtyResults;
}

void DicesReferee::adjustSoldiers(std::vector<CountryLost*> countriesCasualties)
{
    for(int x = 0; x < countriesCasualties.size(); x++){
        Country *ptrCountry = countriesCasualties[x]->getCountry();
        ptrCountry->adjustSoldiers(countriesCasualties.at(x)->getLosses());
    }
}

void DicesReferee::startWar(Country *attacker, int attackerDices, Country *defender, int defenderDices)
{
    std::vector<CountryLost*> casualtyResults;
    casualtyResults = calculateLosses(attacker,attackerDices,defender,defenderDices);
    adjustSoldiers(casualtyResults);
}

DicesReferee* DicesReferee::getInstance()
{
    if(instance == NULL){
        instance = new DicesReferee();
        dices = new Dices(MAX_DICES);
    }
    return instance;
}
