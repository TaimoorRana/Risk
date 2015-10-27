#ifndef BUTTON
#define BUTTON
#include <QPushButton>
#include <QString>
#include "warreferee.h"
class Button: public QPushButton{
public:
    Button(QString label);
public slots:
    void pressed(Country& country);
};

#endif // BUTTON

