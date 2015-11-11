
#include <QDebug>
#include <QString>

#include "map_editor.h"
#include "map_scene.h"
#include "qgraphics_country_item.h"
#include "debug.h"
#include "mainscreen.h"

MapScene::MapScene(RiskMap* map, QWidget *parent){
	this->setParent(parent);
	this->map = map;
}

bool MapScene::getEditable() const {
	return this->editable;
}

void MapScene::setEditable(bool editable) {
	this->editable = editable;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mousePressEvent(event);

	QGraphicsCountryItem *item = nullptr;
	if (!this->editable) {
		item = getQGraphicsCountryItemFromEvent(event);
		item->getCountry()->addArmies(1);
		map->getPlayer(item->getCountry()->getPlayer())->removeReinforcements(1);
		map->getPlayer(item->getCountry()->getPlayer())->notifyObserver();
		debug(std::to_string(item->getCountry()->getArmies()));
		return;
	}

	int xpos =  event->scenePos().x();
	int ypos =  event->scenePos().y();
	QRectF r1(xpos-10,ypos-10,20,20);
	QPen p(QColor(13,145,67,255));
	MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
	CountryNameDialog nameDialog(parent);
	Country* c = nullptr;


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
