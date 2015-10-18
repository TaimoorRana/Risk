#include "dice.h"
#include <cstdlib>
//Dice::Dice(int value)
//{
//    this->MAX_NUMBER = value;
//}

int Dice::roll(){
    int randNumber = rand();
    randNumber = (randNumber % 6) + 1;
    return randNumber;
}

