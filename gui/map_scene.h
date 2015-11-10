#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
//#include <QMutexLocker>
#include <QString>

#include "country_qgraphics_object.h"

#include "risk_map.h"

#include "enum_tooltype.h"

class MapScene: public QGraphicsScene
{
public:
	MapScene(RiskMap* map, QWidget *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    CountryQGraphicsObject* getCountryGraphicsObjAt(QGraphicsSceneMouseEvent *event);

private:
	RiskMap* map = 0;
	Country* lastPicked = 0;
//    mutable QMutex mutex;
    QString lastContinent;
};

#endif // MAP_SCENE_H
