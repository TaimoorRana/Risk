#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include "qgraphics_country_item.h"
#include "risk_map.h"
#include "enum_tooltype.h"

class MapScene: public QGraphicsScene
{
public:
	MapScene(RiskMap* map, QWidget *parent = 0);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		QGraphicsCountryItem* getCountryGraphicsObjAt(QGraphicsSceneMouseEvent *event);

private:
	RiskMap* map = 0;
	Country* lastPicked = 0;
	QString lastContinent;
};

#endif // MAP_SCENE_H
