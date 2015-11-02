#ifndef PLAYERVIEW
#define PLAYERVIEW
#include "playerobserver.h"
#include <string>
#include <set>
class PlayerView: public PlayerObserver{
private:
    std::set<std::string> countriesOwned;
    std::set<std::string> continentsOwned;
    int nbrOfReinforcements;
    int nbrOfArmies;
    int nbrBattleWon;
    int id;
    static int idCounter;

public:
    PlayerView();
    void update (std::set<std::string>,std::set<std::string>,int,int,int);
    std::set<std::string> getCountriesOwned();
    std::set<std::string> getContinentsOwned();
    int getNumberOfReinforcements();
    int getNumberOfArmies();
    int getNumberOfBattleWon();
};

#endif // PLAYERVIEW

