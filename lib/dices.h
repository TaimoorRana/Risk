#ifndef DICES
#define DICES
#include <vector>

class Dices{

private:
    int quantity;
    std::vector<int> results;
public:
    Dices(int quantity);
    std::vector<int> *roll();
    void sort(std::vector<int> *toSort);
};

#endif // DICES

