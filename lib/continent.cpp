#include <cereal/types/string.hpp>

#include "continent.h"


Continent::Continent(const std::string& name) {
	this->name = name;
}

Continent::Continent(const Continent& continent) {
	name = continent.name;
	reinforcementBonus = continent.reinforcementBonus;
}

std::string Continent::getName() const {
	return this->name;
}

void Continent::setName(const std::string& name) {
	this->name = name;
}
int Continent::getReinforcementBonus() const {
	return this->reinforcementBonus;
}

void Continent::setReinforcementBonus(int bonus) {
	this->reinforcementBonus = bonus;
}
