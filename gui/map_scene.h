#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMutexLocker>

#include "country_qgraphics_object.h"

#include "risk_map.h"

#include "enum_tooltype.h"

class MapScene: public QGraphicsScene
{
    mutable QMutex mutex;
public:
	MapScene(RiskMap* map, QWidget *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    CountryQGraphicsObject* getCountryGraphicsObjAt(QGraphicsSceneMouseEvent *event);

private:
	RiskMap* map = 0;
	Country* lastPicked = 0;
};

#endif // MAP_SCENE_H
