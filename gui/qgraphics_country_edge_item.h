#ifndef QGRAPHICSCOUNTRYEDGEITEM_H
#define QGRAPHICSCOUNTRYEDGEITEM_H
#include <QPainter>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "country.h"

class QGraphicsCountryEdgeItem : public QGraphicsLineItem, public Observer
{
	Country* country1 = 0;
	Country* country2 = 0;
public:
	QGraphicsCountryEdgeItem(Country* c1, Country* c2);
	~QGraphicsCountryEdgeItem();
	Country* getCountry1() const;
	Country* getCountry2() const;
	void observedUpdated();
};

#endif // QGRAPHICSCOUNTRYEDGEITEM_H
