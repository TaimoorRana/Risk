#ifndef PLAYEROBSERVER
#define PLAYEROBSERVER
#include <set>
#include <string>
class PlayerObserver{
public:
    /*
     * @std::set<std::string> : list of countries
     * @std::set<std::string> : list of continents
     * @int                   : total reinforcements
     * @int                   : total armies
     * @int                   : total battles won
     */
    virtual void update(std::set<std::string>,std::set<std::string>,int,int,int) = 0;
};

#endif // PLAYEROBSERVER

