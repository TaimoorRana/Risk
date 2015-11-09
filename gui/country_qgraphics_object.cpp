#include <QDebug>
#include "country_qgraphics_object.h"
#include <QTimer>

CountryQGraphicsObject::CountryQGraphicsObject(Country* c)
{
	setFlag(ItemIsSelectable);
	setAcceptTouchEvents(true);
	this->country = c;
}

Country* CountryQGraphicsObject::getCountry() const{
	return this->country;
}


QRectF CountryQGraphicsObject::boundingRect() const{
	return QRectF(-8,-8,16,16);
}

void CountryQGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	QPen pen(Qt::black,1);
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::green));
	painter->drawEllipse(QPointF(0, 0), 5, 5);
	painter->drawText(QPointF(-23,17), QString::fromStdString(country->getName()));
}

void CountryQGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    qDebug("Mouse released within QCountryObj");
    update();
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());
}

void CountryQGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    qDebug("Mouse released within QCountryObj");
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());

    update();
//    this->getCountry()->notifyObservers();
}

void CountryQGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);
//    update();
//    this->getCountry()->notifyObservers();
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());

}

