#include <QColor>
#include <QDebug>
#include <QString>

#include <functional>
#include <random>
#include <vector>

#include "map_editor.h"
#include "map_scene.h"
#include "qgraphics_country_item.h"
#include "fortify_dialog.h"
#include "debug.h"
#include "mainscreen.h"

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

	std::vector<QColor> presetContinentColors;
	presetContinentColors.push_back(QColor(255, 255, 153));
	presetContinentColors.push_back(QColor(255, 204, 255));
	presetContinentColors.push_back(QColor(204, 204, 255));
	presetContinentColors.push_back(QColor(204, 244, 204));
	presetContinentColors.push_back(QColor(255, 219, 157));
	presetContinentColors.push_back(QColor(180, 226, 255));
	presetContinentColors.push_back(QColor(206, 215, 140));
	presetContinentColors.push_back(QColor(255, 152, 199));
	presetContinentColors.push_back(QColor(241, 197, 197));
	presetContinentColors.push_back(QColor(255, 155, 119));

	int i=0;
	QColor color;
	for (auto const &ent1 : this->map->getContinents()) {
		const Continent& continent = ent1.second;
		// Use random colors if we've exhausted the preset ones
		if (i < presetContinentColors.size()) {
			color = presetContinentColors[i];
			i++;
		}
		else {
			color = QColor(color_rand(), color_rand(), color_rand());
		}
		continentPalette.insert(std::pair<const std::string, QColor>(continent.getName(), color));
	}

	seed = 8;
	color_rand = std::bind(std::uniform_int_distribution<int>(0, 255), std::mt19937(seed));

	this->playerPalette.clear();
	std::vector<QColor> presetPlayerColors;
	presetPlayerColors.push_back(QColor(0, 219, 0));
	presetPlayerColors.push_back(QColor(255, 102, 236));
	presetPlayerColors.push_back(QColor(255, 124, 36));
	presetPlayerColors.push_back(QColor(0, 82, 245));
	presetPlayerColors.push_back(QColor(255, 206, 10));
	presetPlayerColors.push_back(QColor(239, 34, 34));
	i=0;
	for (auto const &ent1 : this->map->getPlayers()) {
		const Player& player = ent1.second;
		// Use random colors if we've exhausted the preset ones
		if (i < presetPlayerColors.size()) {
			color = presetPlayerColors[i];
			i++;
		}
		else {
			color = QColor(color_rand(), color_rand(), color_rand());
		}
		debug("test: " + color.name().toStdString());
		playerPalette.insert(std::pair<const std::string, QColor>(player.getName(), color));
	}
}

QColor MapScene::getContinentColor(const std::string& countryName) {
	Continent* continent = this->map->RiskMap::getContinentOfCountry(countryName);
	return this->continentPalette.at(continent->getName());
}

QColor MapScene::getPlayerColor(const std::string& playerName) {
	QColor color;
	if (this->editable) {
		color = QColor(204, 204, 204);
	}
	else {
		color = this->playerPalette.at(playerName);
	}
	return color;
}

bool MapScene::getEditable() const {
	return this->editable;
}

void MapScene::setEditable(bool editable) {
	this->editable = editable;
}

RiskMap* MapScene::getMap() {
	return this->map;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mousePressEvent(event);

	QGraphicsCountryItem *item = nullptr;
	if (!this->editable) {
		MainScreen* parent = qobject_cast<MainScreen*>(this->parent());

		switch(parent->getCurrentMode()) {
			case REINFORCEMENTMODE:
				item = getQGraphicsCountryItemFromEvent(event);
				if (item == nullptr) {
					return;
				}

				if (map->getPlayer(item->getCountry()->getPlayer())->getReinforcements() > 0) {
					map->getPlayer(item->getCountry()->getPlayer())->removeReinforcements(1);
					item->getCountry()->addArmies(1);
				}
				else {
					return;
				}
				map->getPlayer(item->getCountry()->getPlayer())->notifyObserver();
				debug(std::to_string(item->getCountry()->getArmies()));
				break;
			case ATTACKMODE:
			case FORTIFICATIONMODE:
				item = getQGraphicsCountryItemFromEvent(event);
				if (item == nullptr) {
					return;
				}
				else {
					if (lastCountryClicked == nullptr) {
						lastCountryClicked = item->getCountry();
					}
					else {
						std::string firstCountryName = lastCountryClicked->getName();
						std::string secondCountryName = item->getCountry()->getName();

						FortifyDialog* fortificationDialog = new FortifyDialog(lastCountryClicked, item->getCountry());
						fortificationDialog->setWindowTitle(QString::fromStdString("Transfering Armies"));

						// check for adjancency
						if (map->areCountriesAdjacent(firstCountryName, secondCountryName)) {
							if (lastCountryClicked->getPlayer().compare(item->getCountry()->getPlayer()) == 0) {
								// pop-up the transfer window
								fortificationDialog->setOriginCountryName(QString::fromStdString(firstCountryName));
								fortificationDialog->setDestinationCountryName(QString::fromStdString(secondCountryName));
							}
							else {
								// pop-up the transfer window
								fortificationDialog->setOriginCountryName(QString::fromStdString("Different"));
								fortificationDialog->setDestinationCountryName(QString::fromStdString("players"));
							}
						}
						else {
							// pop-up the transfer window
							fortificationDialog->setOriginCountryName(QString::fromStdString("Countries not"));
							fortificationDialog->setDestinationCountryName(QString::fromStdString("adjacent"));
						}
						fortificationDialog->show();
						lastCountryClicked = nullptr;
					}
				}
				break;
			default:
				break;
		}
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

			if (lastCountryClicked != nullptr) {
				map->addNeighbour(item->getCountry()->getName(), lastCountryClicked->getName());
				lastCountryClicked = nullptr;
			}
			else {
				lastCountryClicked = item->getCountry();
			}
			break;

		case REMLINK:
			qDebug("MAPSCENE: Remove link between countries.");
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}

			if (lastCountryClicked != 0) {
				debug("Second pick is " + item->getCountry()->getName());
				map->remNeighbour(item->getCountry()->getName(), lastCountryClicked->getName());
				lastCountryClicked = 0;
			}
			else {
				debug("First pick is " + item->getCountry()->getName());
				lastCountryClicked = item->getCountry();
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
