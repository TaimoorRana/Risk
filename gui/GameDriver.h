#include "player.h"
#include "country.h"

#include <iostream>
#include <stdlib.h>
#ifndef DRIVER
#define DRIVER

using std::cout;
using std::cin;
using std::string;

class GameDriver
{
public:
	static GameDriver getInstance();
	void startGame();

	/**
	* @brief ~GameDriver Destructor
	*/
	~GameDriver();

private:
//	int numPlayers;
//	Player* players = new Player[4];
//	Country* countries[16];
//	Continent* continents[2];
	static GameDriver driver;

	/**
	* @brief GameDriver Default constructor
	*/
	GameDriver();

	/**
	* @brief splashScreen Displays an intro screen and message to the user
	*/
	void showSplashScreen();

	/**
	* @brief setNumberOfPlayers Asks the user to enter the number of players as well as their names
	*/
	void setNumberAndNamesOfPlayers();

	/**
	* @brief assignCountries This function takes a vector of Player objects and assigns countries to each, based on the availability of countries
	*/
	void assignCountries();

	/**
	* @brief randomly reorder thge array of players to simulate throwing the dice and knowing who is player first, second,...
	*/
	void assignPlayersOrder();

	/**
	* @brief getReinforcement Adjusts the number of soldiers the player gets at the beginning of their turn
	* @param aPlayer
	*/
	void getReinforcement(Player& aPlayer);

	/**
	* @brief reinforce Adds a soldier to a country upon clicking the add button
	* @param aCountry
	*/
	void reinforce(Country& aCountry);

	/**
	* @brief reduce Removes soldiers from a country upon clicking the
	* @param aCountry
	*/
	void reduce(Country& aCountry);

	/**
	* @brief attack Takes the attacking and defending country and passes them to the board to arbitrates between them
	* @param atkCountry
	* @param dfndCountry
	*/
	void attack(Country& atkCountry, Country& dfndCountry);

	/**
	* @brief fortify Passes soldier between two adjacent countries before player's turn ends
	* @param origin
	* @param destination
	* @param numSoldiers
	*/
	void fortify(Country& origin, Country& destination, int numSoldiers);
};

#endif // DRIVER

