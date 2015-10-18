#include "continent.h"
#include "debug.h"

Continent::Continent(const std::string& name, int reinforcement_bonus) {
	this->setName(name);
	this->setReinforcementBonus(reinforcement_bonus);
}

Continent::Continent(const Continent& continent) {
	name = continent.name;
	reinforcement_bonus = continent.reinforcement_bonus;
}

std::string Continent::getName() const {
	return this->name;
}
void Continent::setName(const std::string& name) {
	this->name = name;
}

int Continent::getReinforcementBonus() const {
	return this->reinforcement_bonus;
}
void Continent::setReinforcementBonus(int reinforcement_bonus) {
	this->reinforcement_bonus = reinforcement_bonus;
}

const std::vector<Country> Continent::getCountries() const {
	return this->countries;
}
void Continent::addCountry(Country country) {
	this->countries.push_back(country);
}
