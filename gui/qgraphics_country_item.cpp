#include <QDebug>
#include "qgraphics_country_item.h"
//#include <QTimer>

QGraphicsCountryItem::QGraphicsCountryItem(Country* c)
{
	setFlag(ItemIsSelectable);
	setAcceptTouchEvents(true);
	this->country = c;
}

Country* QGraphicsCountryItem::getCountry() const{
	return this->country;
}


QRectF QGraphicsCountryItem::boundingRect() const{
	return QRectF(-8,-8,16,16);
}

void QGraphicsCountryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	QPen pen(Qt::black,1);
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::green));
	painter->drawEllipse(QPointF(0, 0), 5, 5);
	painter->drawText(QPointF(-23,17), QString::fromStdString(country->getName()));
}

void QGraphicsCountryItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    qDebug("Mouse released within QCountryObj");
    update();
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());
}

void QGraphicsCountryItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    qDebug("Mouse released within QCountryObj");
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());

    update();
//    this->getCountry()->notifyObservers();
}

void QGraphicsCountryItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseMoveEvent(event);
//    update();
//    this->getCountry()->notifyObservers();
    qDebug()<< "Mouse was pressed at: "<< QString::fromStdString(country->getName());

}

