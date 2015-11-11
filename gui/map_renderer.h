#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <string>
#include <QGraphicsScene>
#include "country.h"
#include "risk_map.h"

class MapRenderer {
public:
	static void updateScene(RiskMap* map, QGraphicsScene* scene, std::string mapPath, bool editable);

private:
	static void connectNeighboursVisit(RiskMap* map, QGraphicsScene* scene, std::map<const std::string, bool>& visited, Country* country);
};
#endif // MAPRENDERER_H
