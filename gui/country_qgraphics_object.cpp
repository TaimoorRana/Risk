#include <QDebug>
#include "country_qgraphics_object.h"
#include <QTimer>

CountryQGraphicsObject::CountryQGraphicsObject(Country* c)
{
	pressed = false;
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
	QRectF rect = boundingRect();
//	painter->drawRect(rect);
	QPen pen(Qt::black,1);
	painter->setPen(pen);
	painter->setBrush(QBrush(Qt::green));
//	painter->drawEllipse(rect);
	painter->drawEllipse(QPointF(0, 0), 5, 5);
	painter->drawText(QPointF(-23,17), QString::fromStdString(country->getName()));

//	painter->drawEllipse(QPointF(0,0),15,15);
//	painter->drawText(QPointF(-33,27), QString::fromStdString(country->getName()));


//	if (pressed){
//		QPen pen(Qt::red,3);
//		painter->setPen(pen);
//		painter->drawEllipse(rect);
//	}
//	else{
//		QPen pen(Qt::black, 3);
//		painter->setPen(pen);
//		painter->drawRect(rect);
//	}
}

void CountryQGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event){
	pressed = !pressed;
	update();
//	QTimer *t = new QTimer();
//	t->start(500);

	QGraphicsItem::mousePressEvent(event);
	qDebug()<< QString::fromStdString(country->getName());
//	qDebug()<< parentItem()
}

void CountryQGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	pressed = !pressed;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
