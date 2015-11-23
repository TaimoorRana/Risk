#ifndef QGRAPHICSCOUNTRYITEM_H
#define QGRAPHICSCOUNTRYITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "country.h"

class QGraphicsCountryItem: public QGraphicsItem, public Observer
{
	Country *country = 0;
	const int diameter = 10;
	const int fontSize = 9;
public:
	QGraphicsCountryItem(Country* c);
	~QGraphicsCountryItem();
	QRectF boundingRect() const;
	Country* getCountry() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void observedUpdated();
protected:
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QGRAPHICSCOUNTRYITEM_H
