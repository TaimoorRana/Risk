#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <algorithm>
#include <functional>
#include "librisk.h"

/**
 * Common initializations.
 */
void libriskInit() {
	// Seed random number generator with the current time.
	srand(time(NULL));
}

/**
 * @brief Rolls the specified amount of dice and returns the results (random
 * ints) as a vector.
 */
std::vector<int> rollDice(int amount)
{
	std::vector<int> results;
	// generate random numbers depending on "quantity" of dices
	for (unsigned int x = 0; x < amount; x++){
		int randNumber = rand();
		randNumber = (randNumber % 6) + 1;
		results.push_back(randNumber);
	}
	std::sort(results.begin(), results.end(), std::greater<int>());
	return results;
}

/**
 * @brief given a number of cards, determines the correct number of
 * reinforcements to allocate.
 */
int convertCardsToReinforcements(int numCards) {
	int armiesEarned = 0;
	switch (numCards)
	{
		case 2:
			armiesEarned = 2;
			break;
		case 3:
			armiesEarned = 4;
			break;
		case 4:
			armiesEarned = 7;
			break;
		case 5:
			armiesEarned = 10;
			break;
		case 6:
			armiesEarned = 13;
			break;
		case 7:
			armiesEarned = 17;
			break;
		case 8:
			armiesEarned = 21;
			break;
		case 9:
			armiesEarned = 25;
			break;
		case 10:
			armiesEarned = 30;
			break;
		default:
		  armiesEarned = 0;
		  break;
	}
	return armiesEarned;
}
