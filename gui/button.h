#ifndef BUTTON
#define BUTTON
#include <QPushButton>
#include <QString>
#include "warreferee.h"
class Button: public QPushButton{
    Q_OBJECT
public:
    Button(QString label);
public slots:
    void pressed(Player& playerAttacker, Country& attackingCountry, Player& playerDefender, Country& defendingCountry );
    void test();
};

#endif // BUTTON

