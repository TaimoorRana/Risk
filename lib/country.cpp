#include "country.h"
#include "debug.h"

Country::Country(){
    name = "";
    owner = nullptr;
    x = 0;
    y = 0;
    soldiers = 0;
    continent = nullptr;
}

Country::Country(std::string name, Continent& continent, int x, int y) {
	this->setName(name);
	this->setPositionX(x);
	this->setPositionY(y);
	this->setContinent(continent);
	this->setSoldiers(0);
	this->owner = NULL;
	std::vector<Country> neighbours = std::vector<Country>();
}

Country::Country(const Country& country) {
	this->setName(country.getName());
	this->setPositionX(country.getPositionX());
	this->setPositionY(country.getPositionY());
	Continent continent = country.getContinent();
	this->setContinent(continent);
	this->setSoldiers(country.getSoldiers());
	this->setOwner(country.getOwner());
	// TODO: copy vector of adjacent countries (country.neighbours)
}

Country::~Country() {
	delete this->continent;
	delete this->owner;
}

std::string Country::getName() const {
	return this->name;
}
void Country::setName(const std::string name) {
	this->name = name;
}

Continent Country::getContinent() const {
	Continent& continent = *this->continent;
	return continent;
}
void Country::setContinent(Continent& continent) {
	delete this->continent;
	this->continent = new Continent(continent);
}

Player* Country::getOwner() const {
	return this->owner;
}
void Country::setOwner(Player* owner) {
	delete this->owner;
	this->owner = owner == NULL ? owner : new Player(*owner);
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

void Country::addSoldiers(int soldiers)
{
    
    this->soldiers += soldiers;
    
}

void Country::removeSoldiers(int soldiers)
{
    
    this->soldiers -= soldiers;
    
}

std::vector<Country> Country::getNeighbours() const {
	return this->neighbours;
}
void Country::addNeighbour(Country country) {
	this->neighbours.push_back(country);
}
