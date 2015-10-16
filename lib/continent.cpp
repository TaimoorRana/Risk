#include "continent.h"

Continent::Continent(const std::string& name, int score) {
	this->setName(name);
	this->setScore(score);
}

std::string Continent::getName() {
	return this->name;
}
void Continent::setName(const std::string& name) {
	this->name = name;
}

int Continent::getScore() {
	return this->score;
}
void Continent::setScore(int score) {
	this->score = score;
}

std::vector<Country*> Continent::getCountries() {
	return this->countries;
}
void Continent::addCountry(Country* country) {
	this->countries.push_back(country);
}
