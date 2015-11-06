#ifndef STRATEGY_H
#define STRATEGY_H
#include <string>
#include <vector>
#include <set>
#include "country.h"
#include "risk_map.h"


using namespace std;
/**
 * @brief The Strategy class
 * An abstract class which implements the stragety design pattern for allowing the player to
 * decide which enemy to attack
 */
class Strategy
{
public:
    Strategy();
    ~Strategy();
    void setPlayer(string nameOfPlayer);
    void setAttackFrom(string countryName, int numberOfArmiesOnTerritory);
    bool isAttack();
    void getMap(RiskMap map);
    void setCountryAttackFrom(std::string playerCountry);
    string getCountryAttackFrom();
    bool isSameOwner(std::string countryOwner1,std::string countryOwner2);
    int getNumberOfArmies();
    void setAttack(bool attack);

    //may just use map and call internally
    virtual string decideAttackingCountry(RiskMap map);
protected:
    //need list of bordering countreis
    string nameOfPlayer;
    set<string> listOfAttackCountries; //should be a set
    Country *attacker; //see if right or string
    Country *defender;
    //int numberofArmies on territory may need to specify optimal
    int numberOfArmiesOnTerritory;
    bool attack;
    string countryToAttack;
    string currentCountry;

};

#endif // STRATEGY_H
