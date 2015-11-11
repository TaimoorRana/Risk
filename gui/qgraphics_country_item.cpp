#include "qgraphics_country_item.h"
#include "debug.h"

QGraphicsCountryItem::QGraphicsCountryItem(Country* c) {
	this->country = c;
}

Country* QGraphicsCountryItem::getCountry() const {
	return this->country;
}

QRectF QGraphicsCountryItem::boundingRect() const {
	return QRectF(-8,-8,16,16);
}

void QGraphicsCountryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	QPen pen(Qt::black,1);
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::green));
	painter->drawEllipse(QPointF(0, 0), 5, 5);
	painter->drawText(QPointF(-23,17), QString::fromStdString(country->getName()));
}

void QGraphicsCountryItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem::mouseReleaseEvent(event);
	this->country->setPositionX(event->scenePos().x());
	this->country->setPositionY(event->scenePos().y());
	this->country->notifyObservers();
}
