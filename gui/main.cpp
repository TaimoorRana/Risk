#include <iostream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

#include "risk.h"
#include "player.h"
#include "country.h"
#include "dices.h"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
    Dices *dices = new Dices(3);
    std::vector<int> *re = dices->roll();

    for(int x = 0; x < re->size(); x++){
        std::cout << re->at(x) << std::endl;
    }

	return application.exec();
}
