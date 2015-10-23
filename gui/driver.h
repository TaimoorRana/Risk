#import "player.h"
#import "country.h"


#ifndef DRIVER
#define DRIVER


void assignCountries(players& player[]);

/**
 * @brief getReinforcement Adjusts the number of soldiers the player gets at the beginning of their turn
 * @param aPlayer
 */
void getReinforcement(player& aPlayer);

/**
 * @brief reinforce Adds a soldier to a country upon clicking the add button
 * @param aCountry
 */
void reinforce(country& aCountry);

/**
 * @brief reduce Removes soldiers from a country upon clicking the
 * @param aCountry
 */
void reduce(country& aCountry);

/**
 * @brief attack Takes the attacking and defending country and passes them to the board to arbitrates between them
 * @param atkCountry
 * @param dfndCountry
 */
void attack (country& atkCountry, country& dfndCountry);

/**
 * @brief fortify Passes soldier between two adjacent countries before player's turn ends
 * @param origin
 * @param destination
 * @param numSoldiers
 */
void fortify (country& origin, country& destination, int numSoldiers);




#endif // DRIVER

