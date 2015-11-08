#include "librisk.h"
#include "player.h"
#include "graph_adt.h"
#include "risk_map.h"
#include "strategy.h"
#include "computer_player.h"
#include "aggressive.h"
#include "random.h"
#include "defensive.h"
#include <set>
#include <iostream>
#include <string>

using namespace std;
/**
 * @brief main
 * The main program for testing out the strategy pattern
 * We set up a game map with 2 players and the countries they own
 * the number of soldiers on the territory
 * First we use the Random Strategy
 * Then the aggressive strategy
 * The defensive strategy
 * Then the program ends
 * @return
 */

int main() {
    libriskInit();
    //create initial strategy
    //using random Strategy
    Strategy *strategyPattern = new Random();
    RiskMap map = RiskMap();
    int selectStrategy=1;
    cout <<"Select 1 for aggressive strategy\nSelect 2 for defensive\nSelect 3 for random attack strategy\n";
    //cin >> selectStrategy;
    if(selectStrategy==1){

    }
    else if (selectStrategy==2){

    }else{

    }
    bool inGame=false;
    //while loop while in game
    Player human1("human1");
    Player human2("human2");
    ComputerPlayer computer1("computer1");
    strategyPattern->setPlayer("computer1");
    computer1.setStrategy(strategyPattern);
    Continent america("America");
    Country ontario("Ontario");
    Country quebec("Quebec");
    Country newBrunswick ("New Brunswick");
    Country newYork("New York");
    computer1.addCountry("Ontario");
    human1.addCountry("Quebec");
    human1.addCountry("New Brunswick");
    //human1.addCountry("New York");
    computer1.addCountry("New York");
    map.addContinent(america);
    newYork.setPlayer(computer1.getName());
    quebec.setPlayer(human1.getName());
    ontario.setPlayer(human1.getName());
    newBrunswick.setPlayer(computer1.getName());
    //map.addCountry("Quebec", america.getName(), 1);
    // map.addCountry("Ontario",america.getName(),4);
    // map.addCountry("New Brunswick",america.getName(),2);
    // map.addCountry("New York",america.getName(),1);
    //all upper case

    ontario.setArmies(5);
    newYork.setArmies(2);
    quebec.setArmies(3);
    newBrunswick.setArmies(1);
    ontario.setPlayer("computer1");
    quebec.setPlayer("human1");
    newYork.setPlayer("human1");
    newBrunswick.setPlayer("human1");
    map.addCountry(ontario,america.getName());
    map.addCountry(quebec,america.getName());
    map.addCountry(newYork,america.getName());
    map.addCountry(newBrunswick,america.getName());
    map.addNeighbour("Ontario","Quebec");
    map.addNeighbour("Ontario","New York");
    map.addNeighbour("Quebec","New Brunswick");
    map.addNeighbour("Quebec","New York");

    /*Country *ontario = map.getCountry("Ontario");
    Country *quebec = map.getCountry("Quebec");
    Country *newBrunswick = map.getCountry("New Brunswick");
    Country *newYork = map.getCountry("New York");*/
    cout << "Ontario armies "<< ontario.getArmies()<<" "<<ontario.getPlayer()<<endl;
    cout <<"Quebec armies " << quebec.getArmies()<<" "<<quebec.getPlayer()<<endl;
    cout <<"New York armies " <<newYork.getArmies()<<" "<< newYork.getPlayer()<<endl;
    cout << "New Brunswick armies " << newBrunswick.getArmies()<< " "<<newBrunswick.getPlayer()<<endl;
    map.consolePrintListOfNeighbours(ontario.getName());
    map.addPlayer(computer1);
    map.addPlayer(human1);
    cout << "country name "<<map.getCountry("Quebec")->getPlayer();
    computer1.setAttackFrom(ontario.getName(),(ontario.getArmies()));
    cout << "using random strategy pattern" << endl;
    cout<< "who we attavkin " <<strategyPattern->decideAttackingCountry(map)<<"\n";
    map.consolePrintListOfCountries("America");
    set<string> listOfAttackCountries = map.getNeighbours(ontario.getName());
    // cout<< listOfAttackCountries.

    map.consolePrintListOfNeighbours(ontario.getName());
    cout <<"redefining strategy .. using aggressive pattern" << endl;
    //redefining strategy
    strategyPattern  = new Aggressive();
    strategyPattern->setPlayer("computer1");
    computer1.setStrategy(strategyPattern);
    computer1.setAttackFrom(ontario.getName(),(ontario.getArmies()));
    cout<< "who we attavkin " <<strategyPattern->decideAttackingCountry(map)<<"\n";
    cout << "using defensive strategy pattern" << endl;
    strategyPattern  = new Defensive();
    strategyPattern->setPlayer("computer1");
    computer1.setStrategy(strategyPattern);
    computer1.setAttackFrom(ontario.getName(),(ontario.getArmies()));

    cout<< "who we attavkin " <<strategyPattern->decideAttackingCountry(map)<<"\n";

    if(map.areCountriesAdjacent("New York", "Quebec"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    /*if(map.areCountriesAdjacent("China", "Persia"))
        std::cout<<"Countries are adjacent"<<std::endl;
    else
        std::cout<<"Countries are NOT adjacent."<<std::endl;

    map.consolePrintListOfNeighbours("India");

    std::cout<<"Owner of Arabia: " << map.getCountry("Arabia")->getPlayer() << std::endl;
    map.getCountry("Arabia")->setPlayer("Adrianna");
    std::cout<<"Owner of Arabia: " << map.getCountry("Arabia")->getPlayer() << std::endl;

    std::cout << "Armies in Arabia: " << map.getCountry("Arabia")->getArmies() << std::endl;
    map.getCountry("Arabia")->setArmies(10);
    std::cout << "Armies in Arabia: " << map.getCountry("Arabia")->getArmies() << std::endl;

    std::cout << "Country India belongs to: " << map.getContinentOfCountry("India")->getName() << std::endl;
*/
    return 0;
}
