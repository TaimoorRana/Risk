#include <qDebug>

#include "qgraphics_country_edge_item.h"

QGraphicsCountryEdgeItem::QGraphicsCountryEdgeItem(Country* c1, Country* c2) {
	this->country1 = c1;
	this->country2 = c2;

	this->country1->attachObserver(this);
	this->country2->attachObserver(this);
	QGraphicsLineItem::QGraphicsLineItem(c1->getPositionX(), c1->getPositionY(), c2->getPositionX(), c2->getPositionY());
	QPen pen(QColor(0xFF, 0, 0, 0x40));
	pen.setWidth(1);
	this->setPen(pen);
	this->setLine(c1->getPositionX(), c1->getPositionY(), c2->getPositionX(), c2->getPositionY());
}

QGraphicsCountryEdgeItem::~QGraphicsCountryEdgeItem() {
	country1->detachObserver(this);
	country2->detachObserver(this);
}

Country* QGraphicsCountryEdgeItem::getCountry1() const {
	return this->country1;
}

Country* QGraphicsCountryEdgeItem::getCountry2() const {
	return this->country2;
}

void QGraphicsCountryEdgeItem::observedUpdated() {
	this->setLine(this->country1->getPositionX(), this->country1->getPositionY(), this->country2->getPositionX(), this->country2->getPositionY());
}
