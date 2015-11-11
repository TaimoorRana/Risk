#ifndef LIBRISK_H
#define LIBRISK_H
// Without this, NULL won't be defined.
#include <cstdlib>
#include <vector>

void libriskInit();
std::vector<int> rollDice(int);


#endif // LIBRISK_H
