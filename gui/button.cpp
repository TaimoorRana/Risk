#include "button.h"
#include <iostream>

Button::Button(QString label)
{
    this->setText(label);
}

void Button::pressed(Player &playerAttacker, Country &attackingCountry, Player &playerDefender, Country &defendingCountry)
{
    WarReferee war;
    war.startWar(playerAttacker,attackingCountry,playerDefender,defendingCountry);
}

void Button::test()
{
    std::cout << "test";
}
