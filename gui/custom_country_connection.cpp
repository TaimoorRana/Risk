#include <QPen>
#include "custom_country_connection.h"
#include "debug.h"
CustomCountryConnection::CustomCountryConnection(int x1, int y1, int x2, int y2, QGraphicsItem* parent)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    QGraphicsLineItem::QGraphicsLineItem(x1,x2,y1,y2, parent);
    setAcceptHoverEvents(true);
}


 void CustomCountryConnection::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    QPen pen(QColor(0,0,0xFF, 0x40));
    this->setPen(pen);
    this->update();
}

 void CustomCountryConnection::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPen pen(QColor(0xFF,0,0, 0x40));
    this->setPen(pen);
    this->update();
}

void CustomCountryConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen(QColor(0xFF,0,0, 0x40));
    pen.setWidth(2);
//    this->setPen(pen);
    painter->setPen(pen);
    painter->drawLine(x1,y1,x2,y2);
    debug("Called Paint on Line");
}
