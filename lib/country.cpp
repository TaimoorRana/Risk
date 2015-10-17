#include "country.h"
#include "debug.h"

Country::Country(std::string name, std::string continent_name, int x, int y) {
	this->setName(name);
	this->setPositionX(x);
	this->setPositionY(y);
	this->setContinent(continent_name);
}

Country::Country(const Country& country) {
	name = country.name;
	x = country.x;
	y = country.y;
	continent_name = country.continent_name;
}

std::string Country::getName() const {
	return this->name;
}
void Country::setName(const std::string name) {
	this->name = name;
}

std::string Country::getContinent() const {
	return this->continent_name;
}
void Country::setContinent(const std::string& continent) {
	this->continent_name = continent_name;
}

int Country::getPositionX() const {
	return this->x;
}
void Country::setPositionX(int x) {
	this->x = x;
}

int Country::getPositionY() const {
	return this->y;
}
void Country::setPositionY(int y) {
	this->y = y;
}

std::vector<Country> Country::getNeighbours() const {
	return this->neighbours;
}
void Country::addNeighbour(Country country) {
	this->neighbours.push_back(country);
}
