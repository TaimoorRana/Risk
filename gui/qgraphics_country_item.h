#ifndef QGraphicsCountryItem_H
#define QGraphicsCountryItem_H

#include <QPainter>
#include <QGraphicsItem>


#include "country.h"

class QGraphicsCountryItem: public QGraphicsItem
{
	Country* country = 0;
public:
	QGraphicsCountryItem(Country* c);
	QRectF boundingRect() const;
	Country* getCountry() const;
    void deleteCountry();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QGraphicsCountryItem_H
