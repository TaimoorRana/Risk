#ifndef MAP_SCENE_H
#define MAP_SCENE_H
#include <functional>
#include <random>
#include <vector>

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

	RiskMap* getMap();

	/**
	 * @brief observedUpdated
	 * This method uses the observer design pattern to tell the map to update.
	 */
	void observedUpdated();

	QColor getContinentColor(const std::string& countryName);
	QColor getPlayerColor(const std::string& playerName);

	void repopulate(std::string mapPath);

private:
	RiskMap* map = 0; ///< This contains a pointer to the observed map.
	Country* firstCountryClicked = nullptr; ///< This is an auxiliary variable when picking a Country in the Map with the mouse
	Country* secondCountryClicked = nullptr; ///< This is an auxiliary variable when picking a Country in the Map with the mouse
	QString lastContinent; ///< To facilitate entry when creating countries, this variable remembers the last continent used, when adding countries consecutively.
	bool editable = false; ///< This variable controls the difference in behaviour when editing a map and when using the map to play (Then the map is not editable).
	std::map<const std::string, QColor> continentPalette = std::map<const std::string, QColor>(); ///< This map contains the colours used for colouring the continents.
	std::vector<QColor> playerPalette = std::vector<QColor>(); ///< This map containst the colours used for colouring the players
	std::uniform_int_distribution<int> randomDistribution = std::uniform_int_distribution<int>(0, 255);
	std::mt19937 randomGenerator = std::mt19937(8);

	/**
	 * @brief getQGraphicsCountryItemFromEvent
	 * Auxiliary method to retrieve the QCountryGraphicsObject when clicking on the map
	 * @param event Is a mouse event taken from the window
	 * @return
	 */
	QGraphicsCountryItem* getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event);
	void connectNeighboursVisit(std::map<const std::string, bool>& visited, Country* country);
};

#endif // MAP_SCENE_H
