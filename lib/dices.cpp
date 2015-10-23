#include "dices.h"
#include <vector>
#include <cstdlib>
#include <time.h>
Dices::Dices(int quantity)
{
    this->quantity = quantity;
    
    srand(time(NULL));
}

std::vector<int> Dices::roll(int amountOfDices)
{
    results.clear();
    // reset seed

    // generate random numbers depending on "quantity" of dices
    for(unsigned int x = 0; x < amountOfDices; x++){
        int randNumber = rand();
        randNumber = (randNumber % 6) + 1;
        results.push_back(randNumber);
    }

    // sort the results
    sort(&results);

    return results;
}

// bubblesort
void Dices::sort(std::vector<int> *toSort)
{
    for(unsigned int x = 0; x < toSort->size(); x++){
        for(unsigned int y = x + 1; y < toSort->size(); y++){
            if(toSort->at(x) < toSort->at(y)){
                int temp = toSort->at(x);
                toSort->at(x) = toSort->at(y);
                toSort->at(y) = temp;
            }
        }
    }
}




