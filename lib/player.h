#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>
#include "risk_map.h"
#include "playersubject.h"
#include "playerobserver.h"
class Country; // forward declaration

class Player: public PlayerSubject{
private:
    int reinforcements;
    int battleWon;
    int totalArmy;
    std::string name;
    std::set<std::string> namesOfCountriesOwned;
    std::set<std::string> namesOfContinentsOwned;
    RiskMap& map = RiskMap::getInstance();
    std::set<PlayerObserver*> observerList;

public:

	Player(std::string name);
    Player(const Player& other);
    std::string getName();

    // increase battleWon int by 1
    void increaseBattleWon();
    void decreaseBattleWon();
    void setBattlesWon();
    int getBattlesWon();

    /*
     Reinforcements related methods
     @params int: number of soldiers
     */
    void addReinforcements(const int&);
    void removeReinforcements(const int&);
    void setReinforcements(const int&);
    int  getReinforcements();

    /*
     Country related methods
     @params string: countries name
     */
    void addCountry(const std::string&);
    void removeCountry(const std::string&);
    bool hasCountry(const std::string&);
    std::set<std::string> getCountryOwned();

    /*
     continent related methods
     @params string: continents name
    */
    void addContinent(const std::string&);
    void removeContinent(const std::string&);
    bool hasContinent(const std::string&);
    std::set<std::string> getContinentsOwned();


    /*
     * Observer Pattern Methods
     */
    virtual void registerObserver(PlayerObserver*);
    virtual void unregisterObserver(PlayerObserver*);
    virtual void notifyObserver();

    /*
     * Army Related Methods
     */
    int getTotalArmy();
    int setTotalArmy();
};
#endif // PLAYER_H
