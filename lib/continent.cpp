#include "continent.h"
#include "debug.h"

Continent::Continent(const std::string& name, int score) {
	this->setName(name);
	this->setScore(score);
}

Continent::Continent(const Continent& continent) {
	name = continent.name;
	score = continent.score;
	std::vector<Country> countries = continent.countries;
}

std::string Continent::getName() const {
	return this->name;
}
void Continent::setName(const std::string& name) {
	this->name = name;
}

int Continent::getScore() const {
	return this->score;
}
void Continent::setScore(int score) {
	this->score = score;
}

const std::vector<Country> Continent::getCountries() const {
	return this->countries;
}
void Continent::addCountry(Country country) {
	this->countries.push_back(country);
}
