#include <QColor>
#include <QDebug>
#include <QString>

#include <functional>
#include <random>

#include "map_editor.h"
#include "map_scene.h"
#include "qgraphics_country_item.h"
#include "debug.h"

class QGraphicsCountryItem;

MapScene::MapScene(RiskMap* map, QWidget *parent){
	this->setParent(parent);
	this->map = map;
	this->map->attachObserver(this);
}

MapScene::~MapScene() {
	this->map->detachObserver(this);
}

void MapScene::observedUpdated() {
	std::mt19937::result_type seed = 4;
	auto color_rand = std::bind(std::uniform_int_distribution<int>(0, 255), std::mt19937(seed));
	this->continentPalette.clear();
	for (auto const &ent1 : this->map->getContinents()) {
		const Continent& continent = ent1.second;
		continentPalette.insert(std::pair<const std::string, QColor>(continent.getName(), QColor(color_rand(), color_rand(), color_rand())));
	}

	seed = 8;
	color_rand = std::bind(std::uniform_int_distribution<int>(0, 255), std::mt19937(seed));
	this->playerPalette.clear();
	for (auto const &ent1 : this->map->getPlayers()) {
		const Player& player = ent1.second;
		playerPalette.insert(std::pair<const std::string, QColor>(player.getName(), QColor(color_rand(), color_rand(), color_rand())));
	}
}

QColor MapScene::getContinentColor(const std::string& countryName) {
	// FIXME: .at() error handling if element does not exist
	Continent* continent = this->map->RiskMap::getContinentOfCountry(countryName);
	return this->continentPalette.at(continent->getName());
}

QColor MapScene::getPlayerColor(const std::string& playerName) {
	// FIXME: .at() error handling if element does not exist
	return this->playerPalette.at(playerName);
}

bool MapScene::getEditable() const {
	return this->editable;
}

void MapScene::setEditable(bool editable) {
	this->editable = editable;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mousePressEvent(event);

	if (!this->editable) {
		return;
	}

	int xpos =  event->scenePos().x();
	int ypos =  event->scenePos().y();
	QRectF r1(xpos-10,ypos-10,20,20);
	QPen p(QColor(13,145,67,255));
	MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
	CountryNameDialog nameDialog(parent);
	Country* c = nullptr;
	QGraphicsCountryItem *item = nullptr;

	switch(parent->getSelectedTool()){
		case ADDCOUNTRY:
			nameDialog.setLastContinentName(lastContinent);
			if (nameDialog.exec() == QDialog::Rejected) {
				return;
			}

			lastContinent = nameDialog.getContinentName();
			c = map->addCountry(Country(nameDialog.getCountryName().toStdString()), nameDialog.getContinentName().toStdString());
			if (c == nullptr) {
				// FIXME inform user of error
				return;
			}
			c->setPositionX(xpos);
			c->setPositionY(ypos);
			this->map->notifyObservers();
			break;

		case REMCOUNTRY:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}
			map->remCountry(*item->getCountry());
			this->map->notifyObservers();
			break;

		case ADDLINK:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}

			if (lastPicked != nullptr) {
				map->addNeighbour(item->getCountry()->getName(), lastPicked->getName());
				lastPicked = nullptr;
			}
			else {
				lastPicked = item->getCountry();
			}
			break;

		case REMLINK:
		qDebug("MAPSCENE: Remove link between countries.");
		item = getQGraphicsCountryItemFromEvent(event);
		if (item == nullptr) {return;}

		if (lastPicked != 0)
		{
			debug("Second pick is " + item->getCountry()->getName());
			map->remNeighbour(item->getCountry()->getName(), lastPicked->getName());
			lastPicked = 0;
		}
		else
		{
			debug("First pick is " + item->getCountry()->getName());
			lastPicked = item->getCountry();
		}
		case OFF:
		default:
			break;
	}
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mouseReleaseEvent(event);
	// Re-draws the whole scene, fixing text that gets left behind from dragging QGraphicsCountryItem objects (due to their out of bound text)
	this->update();
}

QGraphicsCountryItem* MapScene::getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem *itemAt = nullptr;
	QGraphicsCountryItem *item = nullptr;
	itemAt = this->itemAt(event->scenePos(), QTransform());
	item = dynamic_cast<QGraphicsCountryItem*>(itemAt);
	return item;
}
