#include "country.h"
#include "debug.h"

Country::Country(const std::string& name_country, int n_armies) {
	this->name_of_country=name_country;
	this->setArmies(n_armies);
	this->setPlayer("");
}

Country::Country(const std::string& name): name_of_country(name){}
Country::Country(Country const& country) {
	name_of_country = country.name_of_country;
	armies = country.armies;
	name_of_player = country.name_of_player;
}

std::string Country::getName() const {
	return this->name_of_country;
}

void Country::setName(const std::string& name) {
	this->name_of_country = name;
}

void Country::setPlayer(const std::string& nameOfPlayer){this->name_of_player = nameOfPlayer;}
std::string Country::getPlayer(){
	std::string player(name_of_player);
	return player;
}

void Country::setArmies(const int& armies){this->armies=armies;}
int Country::getArmies(){return armies;}

void Country::removeArmies(const int& amount){
	if (armies - amount >= 0) {
		armies -= amount;
	}
}

void Country::addArmies(const int& amount){
	armies += amount;
}
