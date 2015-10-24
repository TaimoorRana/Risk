#include "continent.h"
#include "debug.h"
#include <iostream>

Continent::Continent(const std::string& name) {
	this->setName(name);
    std::unordered_map<std::string,Country> countries;
}

Continent::Continent(const Continent& continent) {
	name = continent.name;
    std::unordered_map<std::string,Country> countries(continent.countries);
}

std::string Continent::getName() const {
	return this->name;
}
void Continent::setName(const std::string& name) {
	this->name = name;
}

std::unordered_map<std::string,Country> Continent::getCountries() const {
    std::unordered_map<std::string, Country> countries_returned(countries);
    return countries_returned;
}

void Continent::addCountry(const std::string& country_name){
    this->countries[country_name]=Country(country_name);
}
