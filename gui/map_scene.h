#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include "qgraphics_country_item.h"
#include "risk_map.h"
#include "enum_tooltype.h"

class MapScene: public QGraphicsScene, public Observer
{
public:
	MapScene(RiskMap* map, QWidget *parent = 0);
	~MapScene();
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	bool getEditable() const;
	void setEditable(bool editable);
	void observedUpdated();
	QColor getContinentColor(const std::string& countryName);
	QColor getPlayerColor(const std::string& playerName);


private:
	RiskMap* map = 0;
	Country* lastPicked = 0;
    Country* lastCountryClicked = nullptr;
	QString lastContinent;
	QGraphicsCountryItem* getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event);
	bool editable = false;
	std::map<const std::string, QColor> continentPalette = std::map<const std::string, QColor>();
	std::map<const std::string, QColor> playerPalette = std::map<const std::string, QColor>();
};

#endif // MAP_SCENE_H
