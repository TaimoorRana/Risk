#include <iostream>
#include <vector>

#include "librisk.h"
#include "war_referee.h"

WarReferee::WarReferee() {};

/**
 * Calculates the loses each country occurs after the dice roll- if dices are specified
 */
void WarReferee::calculateLosses(int &, int &)
{
	this->attackerDices = attackerDices;
	this->defenderDices = defenderDices;
	calculateLossesHelper();
}


/**
 * Calculates the loses each country occurs after the dice roll - if dices are not specified
 */
void WarReferee::calculateLosses(){
	// Determine amount of dices for the attacker depending on the army size

	if (this->attackerArmy > 3){
		attackerDices = 3;
	}else if(this->attackerArmy  == 3){
		attackerDices = 2;
	}else if(this->attackerArmy  == 2){
		attackerDices = 1;
	}else{
		std::cout << "error in calculateLosses Method\n";
	}

	if(this->defenderArmy  >= 2){
		defenderDices = 2;
	}else if(this->defenderArmy == 1){
		defenderDices = 1;
	}else{
		std::cout << "error in calculateLosses Method\n";
	}

	calculateLossesHelper();
}



/**
 * Calculates the loses each country occurs after the dice roll - HELPER
 */
void WarReferee::calculateLossesHelper(){
	//dices rolled by both players
	std::vector<int> attackerResults = rollDice(attackerDices);
	std::vector<int> defenderResults = rollDice(defenderDices);

	int attackerLosses = 0;
	int defenderLosses = 0;

	 //Compare roll results
	 //Attacker's highest dice is compared to Defender's highest dice
	int dicesToCompare = (defenderDices <= attackerDices)? defenderDices : attackerDices;

	for(int x = 0; x < dicesToCompare; x++){
		if(attackerResults[x] > defenderResults[x]){
			defenderLosses++;
		}else{
			attackerLosses++;
		}
	}



	// Remove soldiers lost from the battle
	if (attackerArmy > attackerLosses) {
		attackerArmy = attackerArmy - attackerLosses;
	}else{
		std::cout << "Error: Could not remove soldiers from attackerCountry\n";
	}
	if (defenderArmy >= defenderLosses) {
		defenderArmy = defenderArmy - defenderLosses;
	}else{
		std::cout << "Error: Could not remove soldiers from defenderCountry\n";
	}
}





void WarReferee::allInMode(){

	while (attackerArmy > 1) {
		calculateLosses();
		if (defenderArmy <= 0) {
			break;
		}
	}
	std::cout << attackerArmy << std::endl;

	if (attackerArmy <= 1 ) {
		std::cout << "Attacker cannot attack anymore\n";
	}else{
		std::cout << "Attacker won and conquered\n";
	}
}


void WarReferee::startWar(std::string& attackerPlayer, int& attackerArmy, std::string& defenderPlayer, int& defenderArmy)
{
	setBothPlayers(attackerPlayer, defenderPlayer);
	this->attackerArmy = attackerArmy;
	this->defenderArmy = defenderArmy;
	allInMode();
}

WarReferee& WarReferee::getInstance()
{
	static WarReferee* instance = nullptr;
	if(instance == nullptr){
		instance = new WarReferee();
	}
	return *instance;
}

void WarReferee::setBothPlayers(std::string& attackerPlayer, std::string& defenderPlayer){
	this->attackerPlayer = attackerPlayer;
	this->defenderPlayer = defenderPlayer;
}


void WarReferee::setAttackerPlayer(std::string& name)
{
	attackerPlayer = name;
}

void WarReferee::setDefenderPlayer(std::string & name)
{
	defenderPlayer = name;
}

void WarReferee::setDefenderArmy(int &army)
{
	attackerArmy = army;
}

void WarReferee::setAttackerArmy(int &army)
{
	defenderArmy = army;
}

void WarReferee::setBothArmies(int &attackerArmy, int &defenderArmy)
{
	this->attackerArmy = attackerArmy;
	this->defenderArmy = defenderArmy;
}



std::string WarReferee::getAttackerPlayer()
{
	return attackerPlayer;
}

std::string WarReferee::getDefenderPlayer()
{
	return defenderPlayer;
}

int WarReferee::getAttackerArmy()
{
	return attackerArmy;
}

int WarReferee::getDefenderArmy()
{
	return defenderArmy;
}

