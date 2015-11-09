#include "country.h"
#include "debug.h"

Country::Country(const std::string& name) {
	this->name = name;
}

Country::Country(const std::string& name, int x, int y, int armies) {
	this->setName(name);
	this->setArmies(armies);
	this->setPlayer("");
	this->setPositionX(x);
	this->setPositionY(y);
}

Country::Country(int x, int y) {
    this->setName("");
    this->setPlayer("");
    this->setPositionX(x);
    this->setPositionY(y);
}

Country::Country(Country const& country) {
	this->name = country.name;
	this->armies = country.armies;
	this->player = country.player;
}

std::string Country::getName() const {
	return this->name;
}

void Country::setName(const std::string& name) {
	this->name = name;
}

void Country::setPlayer(const std::string& playerName) {
	this->player = playerName;
	this->notifyObservers();
}

std::string Country::getPlayer() const {
	return player;
}

void Country::setArmies(const int& armies) {
	this->armies = armies;
	this->notifyObservers();
}

int Country::getArmies() const {
	return this->armies;
}

void Country::removeArmies(const int& amount) {
	if (armies - amount >= 0) {
		this->armies -= amount;
	}
}

void Country::addArmies(const int& amount) {
	this->armies += amount;
}

int Country::getPositionX() const {
	return this->x;
}

void Country::setPositionX(int x) {
	this->x = x;
	this->notifyObservers();
}

int Country::getPositionY() const {
	return this->y;
}

void Country::setPositionY(int y) {
	this->y = y;
	this->notifyObservers();
}
