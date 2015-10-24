#include "dicesreferee.h"
#include "dices.h"
#include <iostream>

DicesReferee::DicesReferee()
{
    dices = new Dices(MAX_DICES);
}





/**
 * Calculates the loses each country occurs after the dice roll- if dices are specified
 */
std::vector<CountryLost*> DicesReferee::calculateLosses(Country& attacker, int attackerDices, Country& defender, int defenderDices)
{
    this->attackerDices = attackerDices;
    this->defenderDices = defenderDices;
    std::vector<CountryLost*> casualtyResults = calculateLossesHelper(attacker, attackerDices, defender, defenderDices);
    
    return casualtyResults;
}





/**
 * Calculates the loses each country occurs after the dice roll - if dices are not specified
 */
std::vector<CountryLost*> DicesReferee::calculateLosses(Country& attacker, Country& defender){
    // Determine amount of dices for the attacker depending on the army size
    
    if (attacker.getSoldiers() >= 4) {
        attackerDices = 3;
    }else if (attacker.getSoldiers() >= 3){
        attackerDices = 2;
    }else{
        attackerDices = 1;
    }
    
    // Determine amount of dices for the defender depending on the army size

    if (defender.getSoldiers() >= 2) {
        defenderDices = 2;
    }else{
        defenderDices = 1;
    }
    
    
    
    std::vector<CountryLost*> casualtyResults = calculateLossesHelper(attacker, attackerDices, defender, defenderDices);
    
    return casualtyResults;
    
}






/**
 * Calculates the loses each country occurs after the dice roll - HELPER
 */
std::vector<CountryLost*> DicesReferee::calculateLossesHelper(Country &attacker, int attackerDices, Country &defender, int defenderDices){
    // dices rolled by both players
    std::vector<int> attackerResults = dices->roll(attackerDices);
    std::vector<int> defenderResults = dices->roll(defenderDices);
    
    int attackerLosses = 0;
    int defenderLosses = 0;
    
    //Compare roll results
    //Attacker's highest dice is compared to Defender's highest dice
    for(int x = 0; x < defenderDices; x++){
        if(attackerResults[x] > defenderResults[x]){
            defenderLosses++;
        }else{
            attackerLosses++;
        }
    }
    
    std::vector<CountryLost*> casualtyResults;
    
    // This objects contains the country object with the number of casualties
    // objects deleted in DicesReferee::removeSoldiers
    CountryLost *attackerLostResult = new CountryLost(attacker,attackerLosses);
    CountryLost *defenderLostResult = new CountryLost(defender,defenderLosses);
    
    casualtyResults.push_back(attackerLostResult);
    casualtyResults.push_back(defenderLostResult);
    
    return casualtyResults;
}


void DicesReferee::allInMode(Country& attacker, Country& defender){
    Player attakerPlayer = attacker.getOwner();
    while (attacker.getSoldiers() > 1 && defender.getOwner().getName() != attacker.getOwner().getName()) {
        std::vector<CountryLost*> casualtyResults = calculateLosses(attacker,defender);
        removeSoldiers(casualtyResults);
        if (defender.getSoldiers() <= 0) {
            defender.setOwner(attakerPlayer);
        }
    }
    std::cout << attacker.getSoldiers();
    
    if (attacker.getSoldiers() <= 1 ) {
        std::cout << "Attacker cannot attack anymore\n";
    }else{
        std::cout << "Attacker won and conquered\n";
        attakerPlayer.transferSoldiers(attacker, defender, attackerDices);
    }
}




/*
 * Remove soldiers lost from the battle
 */
void DicesReferee::removeSoldiers(std::vector<CountryLost*> countriesCasualties)
{
    for(int x = 0; x < countriesCasualties.size(); x++){
        Country& ptrCountry = countriesCasualties[x]->getCountry();
        ptrCountry.adjustSoldiers(countriesCasualties.at(x)->getLosses());
        
        // delete CountryLost Object because the are no longer needed
        delete countriesCasualties[x];
    }

}

void DicesReferee::startWar(Country& attacker, int attackerDices, Country& defender, int defenderDices)
{
    allInMode(attacker, defender);
}


