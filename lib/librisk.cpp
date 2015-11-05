#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <algorithm>

#include "librisk.h"

/**
 * Common initializations.
 */
void libriskInit() {
	// Seed random number generator with the current time.
	srand(time(NULL));
}

/**
 * Rolls the specified amount of dice and returns the results (random ints) as a
 * vector.
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
    std::sort(results.begin(), results.end());
	return results;
}
