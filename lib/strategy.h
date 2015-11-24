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
    /**
     * @brief setPlayer
     * @param nameOfPlayer
     * sets the name of the player
     */
    void setPlayer(string nameOfPlayer);
    /**
     * @brief setAttackFrom
     * @param countryName the country name of the base country to attack from
     * @param numberOfArmiesOnTerritory the number of armies on the territory
     * sets where is the country to attack from and the number of armies.
     */
    void setAttackFrom(string countryName, int numberOfArmiesOnTerritory);
    /**
     * @brief isAttack
     * is there the possibility of currently attacking
     * e.g are all bordering countries players own used to see where can attack
     * @return
     */
    bool isAttack();
    /**
     * @brief getMap
     * @param map
     * gets the map does not copy it
     */
    void getMap(RiskMap map);
    /**
     * @brief setCountryAttackFrom
     * @param playerCountry - the country to attack From
     * sets the country To attack from
     */
    void setCountryAttackFrom(std::string playerCountry);
    /**
     * @brief getCountryAttackFrom
     * get the country to attack from
     * @return
     */
    string getCountryAttackFrom();
    /**
     * @brief isSameOwner
     * @param countryOwner1 -first country
     * @param countryOwner2  -second country
     * checks whether the 2 countries have the same owner and then returns it as
     * a boolean expression
     * @return
     */
    bool isSameOwner(std::string countryOwner1,std::string countryOwner2);
    int getNumberOfArmies();
    void setAttack(bool attack);

    //may just use map and call internally
    /**
     * @brief decideAttackingCountry
     * @param map the current game map
     * Virtual method which uses the map does not copy it to get the current board state.
     * Then decides which territory to attack and returns it.
     * @return
     */
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
