#ifndef DICE
#define DICE
#include <cstdlib>
class Dice{
private:
const int MAX_NUMBER = 6; // dice size ~ example dice with 6 numbers
int lastValue; // last value rolled by this dice
public:
//    Dice(int value);
    int roll();
    void getLastValue();
};

#endif // DICE

