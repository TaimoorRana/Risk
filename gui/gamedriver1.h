#ifndef GAMEDRIVER1_H
#define GAMEDRIVER1_H
#include "map_scene.h"
#include "player.h"
#include "fortify_dialog.h"
#include <string>
#include <set>
using namespace std;
class GameDriver1
{
public:
    //player ordering
    //need using namespace std.
    //player needs to know it his turn
    GameDriver1(MapScene *scene);
    ~GameDriver1();
    void setPlayerName(string s);
    string getPlayerName();
    void calculateReinforcementArmies(Player *p);
    bool allArmiesPlaced;
    void placeArmies(int i);
    void setNumberOfPlayers(int numberOfPlayers);
    //void setMode(Mode m);
    enum Mode{reinforceMode,attackMode,moveMode, endOfTurnMode};
    Mode currentMode= reinforceMode;
    void attackPhase();
    void reinforcePhase();
    void fortificationPhase();
    void endTurn();

private:

    MapScene *scene = nullptr;
    FortifyDialog fortificationDialog;
    int numberOfPlayers;
    string currentPlayerName;
    bool gameBegun;
    bool canFortify;





};

#endif // GAMEDRIVER1_H
