#include "warreferee.h"
#include "dices.h"
#include <iostream>

WarReferee::WarReferee()
{
    dices = new Dices(MAX_DICES);
}

void WarReferee::setPlayers(Player& attacker1, Player& defender1){
    this->defender = &defender1;
    this->attacker = &attacker1;
}


/**
 * Calculates the loses each country occurs after the dice roll- if dices are specified
 */
std::vector<CountryLost*> WarReferee::calculateLosses(Country& attacker, int attackerDices, Country& defender, int defenderDices)
{
    this->attackerDices = attackerDices;
    this->defenderDices = defenderDices;
    std::vector<CountryLost*> casualtyResults = calculateLossesHelper(attacker, attackerDices, defender, defenderDices);
    
    return casualtyResults;
}


/**
 * Calculates the loses each country occurs after the dice roll - if dices are not specified
 */
std::vector<CountryLost*> WarReferee::calculateLosses(Country& attacker, Country& defender){
    // Determine amount of dices for the attacker depending on the army size
    
    if (attacker.getSoldiers() >= 4) {
        attackerDices = 3;
    }else if (attacker.getSoldiers() == 3){
        attackerDices = 2;
    }else if(attacker.getSoldiers() == 2 ){
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
std::vector<CountryLost*> WarReferee::calculateLossesHelper(Country& attackerCountry, int attackerDices, Country& defenderCountry, int defenderDices){
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
    
    if ((defenderCountry.getSoldiers() <= 0 )) {
        std::cout <<"attacker soldiers: "<< attackerCountry.getSoldiers() << "\n";
        std::cout <<"defender soldiers: "<< defenderCountry.getSoldiers() << "\n";
    }
    
    std::vector<CountryLost*> casualtyResults;
    
    // This objects contains the country object with the number of casualties
    // objects deleted in DicesReferee::removeSoldiers
    CountryLost *attackerLostResult = new CountryLost(attackerCountry,attackerLosses);
    CountryLost *defenderLostResult = new CountryLost(defenderCountry,defenderLosses);
    
    casualtyResults.push_back(attackerLostResult);
    casualtyResults.push_back(defenderLostResult);
    
    return casualtyResults;
}


void WarReferee::allInMode(Country& attackerCountry, Country& defenderCountry){
//    Player* attakerPlayer = attacker.getOwner();
//    Player* defenderPlayer = defender.getOwner();
    while (attackerCountry.getSoldiers() > 1 && attackerCountry.getOwner()->getName() != defenderCountry.getOwner()->getName()) {
        std::vector<CountryLost*> casualtyResults = calculateLosses(attackerCountry,defenderCountry);
        removeSoldiers(casualtyResults);
        if (defenderCountry.getSoldiers() <= 0) {
            attacker->addCountry(defenderCountry);
            defenderCountry.setOwner(attacker);
            //defenderPlayer->removeCountry(defender);
        }
    }
    std::cout << attackerCountry.getSoldiers() << std::endl;
    
    if (attackerCountry.getSoldiers() <= 1 ) {
        std::cout << "Attacker cannot attack anymore\n";
    }else{
        std::cout << "Attacker won and conquered\n";
        attacker->transferSoldiers(attackerCountry, defenderCountry, attackerDices);
    }
}




/*
 * Remove soldiers lost from the battle
 */
void WarReferee::removeSoldiers(std::vector<CountryLost*> countriesCasualties)
{
    for(int x = 0; x < countriesCasualties.size(); x++){
        Country& ptrCountry = countriesCasualties[x]->getCountry();
        if(ptrCountry.getSoldiers() >= countriesCasualties.at(x)->getLosses()){
            ptrCountry.adjustSoldiers(countriesCasualties.at(x)->getLosses());
        }
        // delete CountryLost Object because the are no longer needed
        delete countriesCasualties[x];
    }

}

void WarReferee::startWar(Player& attacker,Country& attackerCountry, Player& defender, Country& defenderCountry)
{
    setPlayers(attacker, defender);
    allInMode(attackerCountry,defenderCountry);
}

