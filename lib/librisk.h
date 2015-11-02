#ifndef LIBRISK_H
#define LIBRISK_H
// Without this, NULL won't be defined.
#include <cstdlib>

#include <vector>
#include <unordered_map>

void librisk_init();
std::vector<int> roll_dice(int);


#endif // LIBRISK_H
