#include <iostream>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

#include "risk.h"
#include "player.h"
#include "country.h"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	// QGraphicsScene *scene = new QGraphicsScene();
	// MyPlayer *player =  new MyPlayer;
	// player->setRect(0,0,100,100);
	// player->setFlag(QGraphicsItem::ItemIsFocusable);
	// player->setFocus();
	// scene->addItem(player);
	// QGraphicsView *view = new QGraphicsView(scene);
	// view->show();
	// Player *taimoor = new Player("Taimoor");
	// Country *canada = new Country("Canada");
	// canada->setOwner(taimoor);
	// Country *us = new Country("us");
	// us->setOwner(taimoor);
	// taimoor->addCountry(canada);
	// taimoor->addCountry(us);
	// taimoor->removeCountry(us);
	// taimoor->printCountries();

	return application.exec();
}
