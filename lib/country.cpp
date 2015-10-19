#include "country.h"
#include "debug.h"

Country::Country(std::string name, Continent continent, int x, int y) {
	this->setName(name);
	this->setPositionX(x);
	this->setPositionY(y);
	this->setContinent(continent);
}

Country::Country(const Country& country) {
	name = country.name;
	x = country.x;
	y = country.y;
	continent = new Continent(*country.continent);
	// TODO: copy vector of adjacent countries (country.neighbours)
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
	this->continent = new Continent(continent);
}

Player Country::getOwner() const {
    Player *owner = this->owner;
	return *owner;
}
void Country::setOwner(Player owner) {
	this->owner = &owner;
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

int Country::getSoldiers() const {
	return this->soldiers;
}
void Country::setSoldiers(int soldiers) {
    this->soldiers = soldiers;
}

void Country::adjustSoldiers(int soldiers)
{
    this->soldiers += soldiers;
}

std::vector<Country> Country::getNeighbours() const {
	return this->neighbours;
}
void Country::addNeighbour(Country country) {
	this->neighbours.push_back(country);
}
