#ifndef COUNTRYQGRAPHICSOBJECT_H
#define COUNTRYQGRAPHICSOBJECT_H

#include <QPainter>
#include <QGraphicsItem>


#include "country.h"

class CountryQGraphicsObject: public QGraphicsItem
{
	Country* country = 0;
public:
	CountryQGraphicsObject(Country* c);
	QRectF boundingRect() const;
	Country* getCountry() const;
    void deleteCountry();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // COUNTRYQGRAPHICSOBJECT_H
