#include "country.h"

Country::Country(std::string name, Continent continent, int x, int y) {
	this->setName(name);
	this->setPositionX(x);
	this->setPositionY(y);
}

std::string Country::getName() {
	return this->name;
}
void Country::setName(std::string name) {
	this->name = name;
}

Continent* Country::getContinent() {
	return this->continent;
}
void Country::setContinent(Continent* continent) {
	this->continent = continent;
}

int Country::getPositionX() {
	return this->x;
}
void Country::setPositionX(int x) {
	this->x = x;
}

int Country::getPositionY() {
	return this->y;
}
void Country::setPositionY(int y) {
	this->y = y;
}

std::vector<Country*> Country::getNeighbours() {
	return this->neighbours;
}
void Country::addNeighbour(Country* country) {
	this->neighbours.push_back(country);
}
