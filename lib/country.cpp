#include "country.h"
#include "debug.h"

Country::Country(std::string name, Continent continent, int x, int y) {
	this->setName(name);
	this->setContinent(continent);
}

Country::Country(const Country& country) {
	name = country.name;
    continent = new Continent(country.getContinent());
}


std::string Country::getName() const {
	return this->name;
}
void Country::setName(const std::string name) {
	this->name = name;
}

Continent Country::getContinent() const {
	Continent* continent = this->continent;
	return *continent;
}
void Country::setContinent(Continent continent) {
	this->continent = &continent;
}




