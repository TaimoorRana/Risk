#include "country.h"

Country::Country(const std::string& name) {
	this->name = name;
}

Country::Country(Country const& country) {
	this->name = country.name;
	this->armies = country.armies;
	this->player = country.player;
	this->x = country.x;
	this->y = country.y;
}

std::string Country::getName() const {
	return this->name;
}

void Country::setName(const std::string& name) {
	this->name = name;
}

void Country::setPlayer(const std::string& playerName) {
	this->player = playerName;
}

std::string Country::getPlayer() const {
	return player;
}

void Country::setArmies(const int& armies) {
	this->armies = armies;
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
}

int Country::getPositionY() const {
	return this->y;
}

void Country::setPositionY(int y) {
	this->y = y;
}
