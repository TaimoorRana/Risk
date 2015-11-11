#include <QFileInfo>
#include <QPixmap>
#include <QString>

#include "debug.h"
#include "map_renderer.h"
#include "qgraphics_country_item.h"
#include "qgraphics_country_edge_item.h"

void MapRenderer::updateScene(RiskMap* map, QGraphicsScene* scene, std::string mapPath, bool editable) {
	scene->clear();
	debug("render event");

	QFileInfo mapFile(QString::fromStdString(mapPath));
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	scene->addPixmap(bg);

	for (auto const &ent1 : map->getCountries()) {
		const Country& country = ent1.second;
		QGraphicsCountryItem* item = new QGraphicsCountryItem(map->getCountry(country.getName()));
		if (editable) {
			item->setFlag(QGraphicsItem::ItemIsMovable);
		}
		item->setPos(country.getPositionX(), country.getPositionY());
		scene->addItem(item);
		item->setZValue(10);
	}

	std::map<const std::string, bool> visited = std::map<const std::string, bool>();
	for (auto const &ent1 : map->getCountries()) {
		const Country& country = ent1.second;
		visited.insert(std::pair<const std::string, bool>(country.getName(), false));
	}

	if (map->getCountries().size() == 0) {
		return;
	}

	for (auto const &ent1 : map->getCountries()) {
		const Country& tmpCountry = ent1.second;
		Country* country = map->getCountry(tmpCountry.getName());
		connectNeighboursVisit(map, scene, visited, country);
	}
}

void MapRenderer::connectNeighboursVisit(RiskMap* map, QGraphicsScene* scene, std::map<const std::string, bool>& visited, Country* country) {
	QPen pen(QColor(0xFF, 0, 0, 0x40));
	pen.setWidth(1);

	bool& was_visited = visited.at(country->getName());
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour_str : map->getNeighbours(country->getName())) {
		Country* neighbour = map->getCountry(neighbour_str);
		QGraphicsCountryEdgeItem* line = new QGraphicsCountryEdgeItem(country, neighbour);
		scene->addItem(line);
		line->setZValue(1);
		connectNeighboursVisit(map, scene, visited, neighbour);
	}
}
