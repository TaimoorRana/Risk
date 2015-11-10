#ifndef CUSTOMCOUNTRYCONNECTION_H
#define CUSTOMCOUNTRYCONNECTION_H

#include <QGraphicsLineItem>
#include <QPainter>

class CustomCountryConnection: public QGraphicsLineItem
{
    int x1;
    int y1;
    int x2;
    int y2;
public:
    CustomCountryConnection(int x1, int y1, int x2, int y2, QGraphicsItem* parent);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
};

#endif // CUSTOMCOUNTRYCONNECTION_H
