#include "continent.h"
#include "debug.h"

Continent::Continent(const std::string& name) {
	this->setName(name);
    std::map<std::string,Country> countries;
}

Continent::Continent(const Continent& continent) {
	name = continent.name;
    std::map<std::string,Country> countries(continent.countries);
}

std::string Continent::getName() const {
	return this->name;
}
void Continent::setName(const std::string& name) {
	this->name = name;
}

const std::map<std::string,Country> Continent::getCountries() const {
	return this->countries;
}
void Continent::addCountry(Country country) {
	this->countries.push_back(country);
}
