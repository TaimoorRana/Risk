#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>
#include <vector>
#include "continent.h"

class Continent; //forward declaration
class Player; //forward declaration

class Country {
private:
    std::string name_of_country;
    std::string name_of_player;
    int armies;
public:
    Country():name_of_country(""){}
    Country(const std::string& name_of_country);
    Country(const Country& country);
	std::string getName() const;
    void setName(std::string );
    std::string getName();
    void setPlayer(const std::string&);
    std::string getPlayer();
    void setArmies(const int&);
    int getArmies();
};
#endif // COUNTRY_H
