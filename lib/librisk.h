#ifndef LIBRISK_H
#define LIBRISK_H
// Without this, NULL won't be defined.
#include <cstdlib>
#include <vector>

void libriskInit();
std::vector<int> rollDice(int);
int convertCardsToReinforcements(int numCards);


#endif // LIBRISK_H
