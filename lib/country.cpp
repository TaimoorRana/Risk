#include "country.h"
#include "debug.h"

Country::Country(const std::string& jessica) {
    this->setName(jessica);
}

Country::Country(Country const& country) {
    name_of_country = country.name_of_country;
}


void Country::setName(const std::string name) {
    this->name_of_country = name;
}

std::string Country::getName() const {
    return this->name_of_country;
}

void Country::setPlayer(const std::string& nameOfPlayer){
    this->name_of_player = nameOfPlayer;
}

std::string Country::getPlayer(){
    std::string player(name_of_player);
    return player;
}

void Country::setArmies(const int& armies){
    this->armies=armies;
}

int Country::getArmies(){
    return armies;
}
