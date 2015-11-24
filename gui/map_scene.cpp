#include <QColor>
#include <QDebug>
#include <QString>

#include <functional>
#include <random>
#include <vector>

#include "map_editor.h"
#include "map_scene.h"
#include "qgraphics_country_item.h"
#include "game_driver.h"
#include "fortify_dialog.h"
#include "debug.h"
#include "mainscreen.h"
#include "game_error_dialog.h"

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
	presetContinentColors.push_back(QColor(255, 255, 153)); //baby yellow
	presetContinentColors.push_back(QColor(204, 204, 255)); //light pink
	presetContinentColors.push_back(QColor(255, 204, 255)); //ligh purple
	presetContinentColors.push_back(QColor(255, 219, 157)); //light orange
	presetContinentColors.push_back(QColor(180, 226, 255)); //baby blue
	presetContinentColors.push_back(QColor(204, 244, 204)); //lime green
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
	/**
	 * ! IMPORTANT ! IMPORTANT ! IMPORTANT ! IMPORTANT ! IMPORTANT !IMPORTANT !
	 *
	 * Remember that if you call ANY function in RiskMap that notifies its
	 * observers, the scene is entirely re-rendered and all references we hold to
	 * QGraphicItems past that point will be INVALID.
	 */
	QGraphicsScene::mousePressEvent(event);

	QGraphicsCountryItem *item = nullptr;
	if (!this->editable) {
		MainScreen* parent = qobject_cast<MainScreen*>(this->parent());
		GameDriver* driver = GameDriver::getInstance();
		std::string currentPlayer = driver->getCurrentPlayerName();

		item = getQGraphicsCountryItemFromEvent(event);
		if (item == nullptr) { return; }

		switch (parent->getCurrentMode()) {
			case REINFORCEMENTMODE:
				if(currentPlayer.compare(item->getCountry()->getPlayer()) == 0 ){
					if (map->getPlayer(item->getCountry()->getPlayer())->getReinforcements() > 0) {
						map->getPlayer(item->getCountry()->getPlayer())->removeReinforcements(1);
						item->getCountry()->addArmies(1);
					}
					else {
						GameErrorDialog *outOfReinforcements = new GameErrorDialog(QString::fromStdString("You have 0 reinforcements left."), parent);
						outOfReinforcements->show();
						return;
					}
				}
				else {
					GameErrorDialog *notYourTurn = new GameErrorDialog(QString::fromStdString("You must choose your own country."), parent);
					notYourTurn->show();
					return;
				}
				map->getPlayer(item->getCountry()->getPlayer())->notifyObservers();
				break;
			case ATTACKMODE:
				item = getQGraphicsCountryItemFromEvent(event);
				if (item == nullptr) {
					return;
				}

				if ((firstCountryClicked == nullptr || firstCountryClicked->getName().compare(item->getCountry()->getName()) == 0)
						&& item->getCountry()->getPlayer().compare(currentPlayer) == 0) {
					firstCountryClicked = item->getCountry();
				} else if(item->getCountry()->getPlayer().compare(currentPlayer) != 0 && firstCountryClicked == nullptr){
					GameErrorDialog *notYourTurn = new GameErrorDialog(QString::fromStdString("You must choose your own country."), parent);
					notYourTurn->show();
					return;
				}
				else {
					secondCountryClicked = item->getCountry();
					if (firstCountryClicked->getPlayer().compare(secondCountryClicked->getPlayer()) != 0 && map->areCountriesAdjacent(firstCountryClicked->getName(), secondCountryClicked->getName())){
						WarReferee warreferee = WarReferee::getInstance();
						warreferee.startWar(firstCountryClicked, secondCountryClicked);

					}else if(!map->areCountriesAdjacent(firstCountryClicked->getName(), secondCountryClicked->getName())){
						GameErrorDialog *notYourTurn = new GameErrorDialog(QString::fromStdString("You can only attack adjacent countries."), parent);
						notYourTurn->show();
						return;
					}
					firstCountryClicked = nullptr;
					secondCountryClicked = nullptr;
				}
			break;
			case FORTIFICATIONMODE:
				if (currentPlayer.compare(item->getCountry()->getPlayer()) != 0) {
					GameErrorDialog *notYourTurn = new GameErrorDialog(QString::fromStdString("You must choose your own country."), parent);
					notYourTurn->show();
					return;
				}
				if (firstCountryClicked == nullptr || firstCountryClicked->getName().compare(item->getCountry()->getName()) == 0) {
					firstCountryClicked = item->getCountry();
				}
				else {
					std::string firstCountryName = firstCountryClicked->getName();
					std::string secondCountryName = item->getCountry()->getName();

					FortifyDialog* fortificationDialog = new FortifyDialog(firstCountryClicked, item->getCountry(), parent);
					fortificationDialog->setWindowTitle(QString::fromStdString("Transferring Armies"));

					// check for adjacency
					if (map->areCountriesAdjacent(firstCountryName, secondCountryName)) {
						// pop-up the transfer window
						fortificationDialog->setOriginCountryName(QString::fromStdString(firstCountryName));
						fortificationDialog->setDestinationCountryName(QString::fromStdString(secondCountryName));
						fortificationDialog->show();
					}
					else {
						GameErrorDialog *selectedNotAdjacent = new GameErrorDialog(QString::fromStdString("Countries are not adjacent."), parent);
						selectedNotAdjacent->show();
					}
					firstCountryClicked = nullptr;
				}
				break;
			default:
				break;
		}
		return;
	}

	int xpos =  event->scenePos().x();
	int ypos =  event->scenePos().y();
	QRectF r1(xpos-10, ypos-10, 20, 20);
	QPen p(QColor(13, 145, 67, 255));
	MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
	CountryNameDialog nameDialog(parent);
	Country* c = nullptr;

	switch (parent->getSelectedTool()) {
		case ADDCOUNTRY:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				nameDialog.setLastContinentName(lastContinent);
				if (nameDialog.exec() == QDialog::Rejected) {
					return;
				}

				lastContinent = nameDialog.getContinentName();
				c = map->addCountry(Country(nameDialog.getCountryName().toStdString()), nameDialog.getContinentName().toStdString());
				if (c == nullptr) {
					GameErrorDialog *cantAddCountry = new GameErrorDialog(QString::fromStdString("Could not add country."), parent);
					cantAddCountry->show();
					return;
				}
				c->setPositionX(xpos);
				c->setPositionY(ypos);
				c->notifyObservers();
			}
			else{
				nameDialog.setExistingCountryName(QString::fromStdString(item->getCountry()->getName()));
				nameDialog.setLastContinentName(QString::fromStdString(map->getContinentOfCountry(item->getCountry()->getName())->getName()));
				nameDialog.disableContinentEntry();
				if (nameDialog.exec() == QDialog::Rejected) {
					return;
				}
				map->renameCountry(item->getCountry()->getName(), nameDialog.getCountryName().toStdString());
			}
			break;

		case REMCOUNTRY:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}
			map->remCountry(*item->getCountry());
			break;

			case ADDLINK:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}

			if (firstCountryClicked != nullptr) {
				map->addNeighbour(item->getCountry()->getName(), firstCountryClicked->getName());
				firstCountryClicked = nullptr;
			}
			else {
				firstCountryClicked = item->getCountry();
			}
			break;

		case REMLINK:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}

			if (firstCountryClicked != 0) {
				map->remNeighbour(item->getCountry()->getName(), firstCountryClicked->getName());
				firstCountryClicked = 0;
			}
			else {
				firstCountryClicked = item->getCountry();
			}
		case OFF:
			default:
			break;
	}
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mouseReleaseEvent(event);

	if (this->editable) {
		MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
		if (parent->getSelectedTool() == OFF) {
			// Re-draws the whole scene, fixing text that gets left behind from dragging QGraphicsCountryItem objects (due to their out of bound text)
			this->map->notifyObservers();
		}
	}
}

QGraphicsCountryItem* MapScene::getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem *itemAt = nullptr;
	QGraphicsCountryItem *item = nullptr;
	itemAt = this->itemAt(event->scenePos(), QTransform());
	item = dynamic_cast<QGraphicsCountryItem*>(itemAt);
	return item;
}
