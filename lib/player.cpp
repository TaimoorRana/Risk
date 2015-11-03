#include <iostream>
#include <string>
#include "country.h"
#include "player.h"

Player::Player(std::string name)
{
	this->name = name;
}

std::string Player::getName() const {
	return this->name;
}

void Player::setName(const std::string& name) {
	this->name = name;
}
