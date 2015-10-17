
#include <string>
#include "country.h"
#include "player.h"
Country::Country(std::string name)
{
    this->name = name;
}

int Country::getTotalSoldiers()
{
    return soldiers;
}

std::string Country::getName()
{
    return name;
}

Player * Country::getOwner()
{
    return this->owner;
}

void Country::setOwner(Player *owner)
{
    this->owner = owner;
}

bool Country::addSoldiers(int amount)
{
    this->soldiers += amount;
    return true;
}

bool Country::removeSoldiers(int amount)
{
    this->soldiers -= amount;
    return true;
}

bool Country::hasSoldiers()
{
    if(soldiers > 0)
        return true;
    else
        return false;
}
