#include "country.h"
#include "player.h"
#include <algorithm>

Player::Player(std::string name){
	this->name = name;
}

std::string Player::getName() const {
	return name;
}

int Player::getCards()
{
		return cards;
}

int Player::updateCards(int numberOfCards)
{
	cards += numberOfCards;
	this->notifyObservers();
	return cards;
}

bool Player::getDidWinCountry()
{
		return didWinCountry;
}

void Player::setDidWinCountry(bool value)
{
		didWinCountry = value;
}

void Player::setReinforcements(const int& amount) {
	reinforcements = amount;
	this->notifyObservers();
}

void Player::adjustReinforcements(const int& amount) {
	reinforcements += amount;
	this->notifyObservers();
}

int Player::getReinforcements() const {
	return this->reinforcements;
}

void Player::setHuman(bool human)
{
	this->human = human;
}

void Player::died()
{
	alive = false;
}

bool Player::isAlive() const
{
	return alive;
}


bool Player::isHuman(){
	return human;
}

void Player::setBattlesWon(const int &amount) {
	this->battleWon = amount;
	this->notifyObservers();
}

void Player::adjustBattlesWon(const int &amount) {
	this->battleWon += amount;
	this->notifyObservers();
}

int Player::getBattlesWon() const {
	return battleWon;
}

void Player::setBattlesLost(const int &amount) {
	this->battleLost = amount;
	this->notifyObservers();
}

void Player::adjustBattlesLost(const int &amount) {
	this->battleLost += amount;
	this->notifyObservers();
}

int Player::getBattlesLost() const {
	return battleLost;
}
