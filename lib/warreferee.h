#ifndef DICESREFEREE
#define DICESREFEREE
#include "dices.h"
#include "country.h"
#include "player.h"
class WarReferee{

//use singleton pattern
private:
    
    static const int MAX_DICES = 3;
    
    // Players
    std::string attackerPlayer;
    std::string defenderPlayer;
    
    // players armies
    int attackerArmy;
    int defenderArmy;

    // dices used by the players
    Dices *dices;
    int defenderDices;
    int attackerDices;
    WarReferee();
public:
    static WarReferee& getInstance();

    void setAttackerPlayer(std::string&);
    void setDefenderPlayer(std::string&);
    void setBothPlayers(std::string& , std::string&);
    std::string getAttackerPlayer();
    std::string getDefenderPlayer();

    void setDefenderArmy(int&);
    void setAttackerArmy(int&);
    void setBothArmies(int&,int&);
    int getAttackerArmy();
    int getDefenderArmy();


    void calculateLossesHelper();
    void calculateLosses();
    void calculateLosses(int attackerDices, int defenderDices);
    void startWar(std::string& attackerPlayer, int& attakerArmy, std::string& defenderPlayer, int& defenderArmy);
    void allInMode();
    ~WarReferee();
};


#endif // DICESREFEREE

