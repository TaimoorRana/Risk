#include "country.h"
#include "player.h"
#include <algorithm>

Player::Player(std::string name){
	this->name = name;
}

void Player::addCountry(const std::string& countryName){
	namesOfCountriesOwned.insert(countryName);
	this->notifyObservers();
}

void Player::removeCountry(const std::string& countryName)
{
	std::set<std::string>::iterator countryOwnedIterator;
	int index = 0;
	for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
		index++;
		if(*countryOwnedIterator == countryName){
			namesOfCountriesOwned.erase(countryOwnedIterator);
			this->notifyObservers();
			break;
		}
	}
}

bool Player::hasCountry(const std::string& countryName) const {
	 std::set<std::string>::iterator countryOwnedIterator;
	 for(countryOwnedIterator = namesOfCountriesOwned.begin(); countryOwnedIterator != namesOfCountriesOwned.end();countryOwnedIterator++){
		if(*countryOwnedIterator == countryName){
			return true;
		}
	}
	return false;
}

bool Player::hasContinent(const std::string& continentName) const {
	std::set<std::string>::iterator continentsOwnedIterator;
	for (continentsOwnedIterator = namesOfContinentsOwned.begin(); continentsOwnedIterator != namesOfContinentsOwned.end(); continentsOwnedIterator++) {
		if (*continentsOwnedIterator == continentName ) {
			return true;
		}
	}
	return false;
}

std::set<std::string> Player::getContinentsOwned() const {
	return this->namesOfContinentsOwned;
}

std::string Player::getName() const {
	return name;
}

void Player::addReinforcements(const int& amount) {
	reinforcements += amount;
	this->notifyObservers();
}

void Player::removeReinforcements(const int& amount) {
	if((reinforcements - amount) >= 0 ){
		reinforcements -= amount;
		this->notifyObservers();
	}
}

void Player::setReinforcements(const int& amount) {
	reinforcements = amount;
	this->notifyObservers();
}

int Player::getReinforcements() const {
	return this->reinforcements;
}

void Player::setTotalArmy(const int &totalArmy) {
	this->totalArmy = totalArmy;
	this->notifyObservers();
}

int Player::getTotalArmy() const {
	return totalArmy;
}

std::set<std::string> Player::getCountriesOwned(){
	std::set<std::string> copy(namesOfCountriesOwned);
	return copy;
}

void Player::increaseBattleWon(){
	battleWon++;
	this->notifyObservers();
}

void Player::decreaseBattleWon() {
	battleWon--;
	this->notifyObservers();
}

void Player::setBattlesWon(const int &battleWon) {
	this->battleWon = battleWon;
	this->notifyObservers();
}

int Player::getBattlesWon() const {
	return battleWon;
}
