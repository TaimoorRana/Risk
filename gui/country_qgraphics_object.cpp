#include "country_qgraphics_object.h"

CountryQGraphicsObject::CountryQGraphicsObject(Country* c)
{
	pressed = false;
	setFlag(ItemIsMovable);
	country = c;
}

QRectF CountryQGraphicsObject::boundingRect() const{
	return QRectF(0,0,20,20);
}

void CountryQGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	QRectF rect = boundingRect();
	QPen pen(Qt::black,1);
	painter->setPen(pen);
//	painter->drawEllipse(rect);
	painter->drawEllipse(QPointF(0,0),5,5);
	painter->drawText(QPointF(-23,17), QString::fromStdString(country->getName()));

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
	QGraphicsItem::mousePressEvent(event);
}

void CountryQGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	pressed = !pressed;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}
