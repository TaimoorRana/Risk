#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "risk_map.h"

#include "enum_tooltype.h"

class MapScene: public QGraphicsScene
{
public:
	MapScene(RiskMap* map, QWidget *parent = 0);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
	RiskMap* map;
};

#endif // MAP_SCENE_H
