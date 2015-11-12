#include "qgraphics_country_item.h"
#include "debug.h"
#include "map_scene.h"

class MapScene;

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
	int diameter = 0;
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	MapScene* parent = dynamic_cast<MapScene*>(this->scene());

	diameter = 10;
	painter->setBrush(QBrush(parent->getContinentColor(this->country->getName())));
	painter->drawEllipse(QPointF(0, 0), diameter, diameter);

	diameter = 5;
	painter->setBrush(QBrush(parent->getPlayerColor(this->country->getPlayer())));
	painter->drawEllipse(QPointF(0, 0), diameter, diameter);

	std::string label = country->getName() + " (" + std::to_string(country->getArmies()) + ")";
	painter->drawText(QPointF(-23,17), QString::fromStdString(label));
}

void QGraphicsCountryItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem::mouseReleaseEvent(event);
	this->country->setPositionX(event->scenePos().x());
	this->country->setPositionY(event->scenePos().y());
	this->country->notifyObservers();
}
