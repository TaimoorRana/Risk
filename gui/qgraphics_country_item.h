#ifndef QGRAPHICSCOUNTRYITEM_H
#define QGRAPHICSCOUNTRYITEM_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "country.h"

class QGraphicsCountryItem: public QGraphicsItem
{
	Country *country = 0;
	const int diameter = 10;
	const int fontSize = 9;
public:
	QGraphicsCountryItem(Country* c);
	QRectF boundingRect() const;
	Country* getCountry() const;
    void setCountry(Country *c);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QGRAPHICSCOUNTRYITEM_H
