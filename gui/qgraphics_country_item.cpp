#include <QBrush>
#include <QFont>
#include <QFontMetrics>
#include <QPen>

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
	return QRectF(-diameter, -diameter, diameter*2, diameter*2);
}

void QGraphicsCountryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	QPen pen(Qt::black, 1);
	painter->setPen(pen);

	MapScene* parent = dynamic_cast<MapScene*>(this->scene());

	// Enable me to view the bounding rectangle
	// painter->setBrush(QBrush(Qt::black));
	// painter->drawRect(this->boundingRect());

	painter->setBrush(QBrush(parent->getContinentColor(this->country->getName())));
	painter->drawEllipse(QPointF(0, 0), this->diameter, this->diameter);

	painter->setBrush(QBrush(parent->getPlayerColor(this->country->getPlayer())));
	painter->drawEllipse(QPointF(0, 0), this->diameter/2, this->diameter/2);

    QFont font = QFont("Open Sans", this->fontSize);
	QFontMetrics metrics(font);
	painter->setFont(font);
	std::string label = country->getName() + " (" + std::to_string(country->getArmies()) + ")";
	int textWidth = metrics.width(QString::fromStdString(label))/2;
    painter->drawText(QPointF(-textWidth, 19), QString::fromStdString(label));
}

void QGraphicsCountryItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem::mouseReleaseEvent(event);
	this->country->setPositionX(event->scenePos().x());
	this->country->setPositionY(event->scenePos().y());
	this->country->notifyObservers();
}
