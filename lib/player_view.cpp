#include "player_view.h"


void PlayerView::update(std::set<std::string> countriesOwnedList, std::set<std::string>continentsOwnedList, int reinforcements, int totalArmies, int totalBattleWon)
{
	this->countriesOwned = countriesOwnedList;
	this->continentsOwned = continentsOwnedList;
	this->nbrOfReinforcements = reinforcements;
	this->nbrOfArmies = totalArmies;
	this->nbrBattleWon = totalBattleWon;
}

std::set<std::string> PlayerView::getCountriesOwned() const
{
	return this->countriesOwned;
}

std::set<std::string> PlayerView::getContinentsOwned() const
{
	return this->continentsOwned;
}

int PlayerView::getNumberOfReinforcements() const
{
	return this->nbrOfReinforcements;
}

int PlayerView::getNumberOfArmies() const
{
	return this->nbrOfArmies;
}

int PlayerView::getNumberOfBattleWon() const
{
	return this->nbrBattleWon;
}
