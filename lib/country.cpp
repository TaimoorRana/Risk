#include "country.h"
#include "debug.h"

Country::Country(const std::string& name_country, int n_armies) {
    this->setNameCountry(name_country);
    this->setArmies(n_armies);
    this->setPlayer("");
}

Country::Country(const std::string& name): name_of_country(name){}
Country::Country(Country const& country) { name_of_country = country.name_of_country;}

void Country::setNameCountry(const std::string name) { this->name_of_country = name;}
std::string Country::getNameCountry() const {return this->name_of_country;}
void Country::setPlayer(const std::string& nameOfPlayer){this->name_of_player = nameOfPlayer;}
std::string Country::getPlayer(){
    std::string player(name_of_player);
    return player;
}

void Country::setArmies(const int& armies){this->armies=armies;}
int Country::getArmies(){return armies;}
