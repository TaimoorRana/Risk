#include <QColor>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>
#include <QString>

#include "map_editor.h"
#include "map_scene.h"

#include "game_driver.h"
#include "fortify_dialog.h"
#include "mainscreen.h"
#include "qgraphics_country_item.h"
#include "qgraphics_country_edge_item.h"

class QGraphicsCountryItem;

MapScene::MapScene(GameDriver* driver, QWidget *parent){
	this->setParent(parent);
	this->driver = driver;
	this->driver->getRiskMap()->attachObserver(this);

	this->playerPalette.push_back(QColor(0, 219, 0));
	this->playerPalette.push_back(QColor(255, 102, 236));
	this->playerPalette.push_back(QColor(255, 124, 36));
	this->playerPalette.push_back(QColor(0, 82, 245));
	this->playerPalette.push_back(QColor(255, 206, 10));
	this->playerPalette.push_back(QColor(239, 34, 34));
}

MapScene::~MapScene() {
	this->driver->getRiskMap()->detachObserver(this);
}

/**
 * @brief Observer notification to re-renders the scene
 * Uses the observer design pattern to tell the map to update
 */
void MapScene::observedUpdated() {
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
	auto color_rand = std::bind(randomDistribution, randomGenerator);
	QColor color;
	for (auto const &ent1 : this->driver->getRiskMap()->getContinents()) {
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
}

/**
 * @brief Gets the QColor object for a given country
 */
QColor MapScene::getContinentColor(const std::string& countryName) {
	Continent* continent = this->driver->getRiskMap()->getContinentOfCountry(countryName);
	return this->continentPalette.at(continent->getName());
}

/**
 * @brief Gets the QColor object for a given player
 */
QColor MapScene::getPlayerColor(const std::string& playerName) {
	if (this->editable) {
		return QColor(204, 204, 204);
	}
	RiskMap* map = this->driver->getRiskMap();

	auto color_rand = std::bind(randomDistribution, randomGenerator);
	int index = std::distance(map->getPlayers().begin(), map->getPlayers().find(playerName));
	if (index < this->playerPalette.size()) {
		return this->playerPalette[index];
	}
	else {
		return QColor(color_rand(), color_rand(), color_rand());
	}
}

/**
 * @brief Gets the editable status of the scene
 */
bool MapScene::getEditable() const {
	return this->editable;
}

/**
 * @brief Sets the editable status of the scene
 */
void MapScene::setEditable(bool editable) {
	this->editable = editable;
}

void MapScene::launchCardsTradeDialog()
{
//    MainScreen* parent = qobject_cast<MainScreen*>(this->parent());
//    CardsTradeDialog* cardsTradeDialog = new CardsTradeDialog(this->driver, parent);
//    cardsTradeDialog->exec();
}

/**
 * @brief Handles mouse presses on the graphics scene GUI widget
 */
void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	/**
	 * ! IMPORTANT ! IMPORTANT ! IMPORTANT ! IMPORTANT ! IMPORTANT !IMPORTANT !
	 *
	 * Remember that if you call ANY function in RiskMap that notifies its
	 * observers, the scene is entirely re-rendered and all references we hold to
	 * QGraphicItems past that point will be INVALID.
	 */
	QGraphicsScene::mousePressEvent(event);

	RiskMap* map = this->driver->getRiskMap();
	QGraphicsCountryItem *item = nullptr;
	if (!this->editable) {
		MainScreen* parent = qobject_cast<MainScreen*>(this->parent());
		std::string currentPlayer = this->driver->getCurrentPlayerName();

		item = getQGraphicsCountryItemFromEvent(event);
		if (item == nullptr) { return; }

		switch (this->driver->getCurrentMode()) {
			case REINFORCEMENT:
				if (currentPlayer.compare(item->getCountry()->getPlayer()) == 0) {

					if (map->getPlayer(item->getCountry()->getPlayer())->getReinforcements() > 0) {
						map->getPlayer(item->getCountry()->getPlayer())->adjustReinforcements(-1);
						item->getCountry()->addArmies(1);
					}
					else {
						QMessageBox errorDialog(parent);
						errorDialog.setWindowTitle("Invalid move");
						errorDialog.setText("You have no more reinforcements left.");
						errorDialog.exec();
						return;
					}
				}
				else {
					QMessageBox errorDialog(parent);
					errorDialog.setWindowTitle("Invalid move");
					errorDialog.setText("You must choose your own country.");
					errorDialog.exec();
					return;
				}
				break;
			case ATTACK:
				item = getQGraphicsCountryItemFromEvent(event);

				if (item == nullptr) {
					return;
				}

				if ((firstCountryClicked == nullptr || firstCountryClicked->getName().compare(item->getCountry()->getName()) == 0)
						&& item->getCountry()->getPlayer().compare(currentPlayer) == 0) {
					firstCountryClicked = item->getCountry();
				}
				else if (item->getCountry()->getPlayer().compare(currentPlayer) != 0 && firstCountryClicked == nullptr) {
					QMessageBox errorDialog(parent);
					errorDialog.setWindowTitle("Invalid move");
					errorDialog.setText("You must choose your own country.");
					errorDialog.exec();
					return;
				}
				else {
					secondCountryClicked = item->getCountry();
					if (firstCountryClicked->getPlayer().compare(secondCountryClicked->getPlayer()) != 0 && map->areCountriesNeighbours(firstCountryClicked->getName(), secondCountryClicked->getName())){
						this->driver->attackCountry(firstCountryClicked, secondCountryClicked);
					}
					else if (!map->areCountriesNeighbours(firstCountryClicked->getName(), secondCountryClicked->getName())) {
						QMessageBox errorDialog(parent);
						errorDialog.setWindowTitle("Invalid move");
						errorDialog.setText("You can only attack adjacent countries.");
						errorDialog.exec();
						return;
					}
					firstCountryClicked = nullptr;
					secondCountryClicked = nullptr;

				}
				break;
			case FORTIFICATION:
				if (currentPlayer.compare(item->getCountry()->getPlayer()) != 0) {
					QMessageBox errorDialog(parent);
					errorDialog.setWindowTitle("Invalid move");
					errorDialog.setText("You must choose your own country.");
					errorDialog.exec();
					return;
				}
				if (firstCountryClicked == nullptr || firstCountryClicked->getName().compare(item->getCountry()->getName()) == 0) {
					firstCountryClicked = item->getCountry();
				}
				else {
					// check for adjacency
					secondCountryClicked = item->getCountry();
					if (map->areCountriesNeighbours(firstCountryClicked->getName(), secondCountryClicked->getName())) {
						FortifyDialog* fortificationDialog = new FortifyDialog(this->driver, firstCountryClicked, secondCountryClicked, parent);
						if (fortificationDialog->exec() == QDialog::Accepted) {
							parent->endPhase();
						}
					}
					else {
						QMessageBox errorDialog(parent);
						errorDialog.setWindowTitle("Invalid move");
						errorDialog.setText("Countries are not adjacent.");
						errorDialog.exec();
					}
					firstCountryClicked = nullptr;
				}
				break;
			default:
				break;
		}
		map->notifyObservers();
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
		case ADD_COUNTRY:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				nameDialog.setLastContinentName(lastContinent);
				if (nameDialog.exec() == QDialog::Rejected) {
					return;
				}

				lastContinent = nameDialog.getContinentName();
				c = map->addCountry(Country(nameDialog.getCountryName().toStdString()), nameDialog.getContinentName().toStdString());
				if (c == nullptr) {
					QMessageBox errorDialog(parent);
					errorDialog.setWindowTitle("Error adding country");
					errorDialog.setText("Could not add country: ensure that a country by that name doesn't already exist.");
					errorDialog.exec();
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

		case REMOVE_COUNTRY:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}
			map->removeCountry(*item->getCountry());
			break;

			case ADD_LINK:
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

		case REMOVE_LINK:
			item = getQGraphicsCountryItemFromEvent(event);
			if (item == nullptr) {
				return;
			}

			if (firstCountryClicked != 0) {
				map->removeNeighbour(item->getCountry()->getName(), firstCountryClicked->getName());
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

/**
 * @brief Handles mouse releases on the graphics scene GUI widget
 */
void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mouseReleaseEvent(event);

	if (this->editable) {
		MapEditor* parent = qobject_cast<MapEditor*>(this->parent());
		if (parent->getSelectedTool() == OFF) {
			// Re-draws the whole scene, fixing text that gets left behind from dragging QGraphicsCountryItem objects (due to their out of bound text)
			this->driver->getRiskMap()->notifyObservers();
		}
	}
}

/**
 * @brief Returns the QGraphicsCountryItem clicked on (if any).
 * Auxiliary method to retrieve the QCountryGraphicsObject when clicking on the map
 * @param event The scene's click event details
 */
QGraphicsCountryItem* MapScene::getQGraphicsCountryItemFromEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsItem *itemAt = nullptr;
	QGraphicsCountryItem *item = nullptr;
	itemAt = this->itemAt(event->scenePos(), QTransform());
	item = dynamic_cast<QGraphicsCountryItem*>(itemAt);
	return item;
}

/**
 * @brief Clears a scene and repopulates it with QGraphicItems based on the state of the observed RiskMap
 */
void MapScene::repopulate(std::string mapPath) {
	this->clear();

	QFileInfo mapFile(QString::fromStdString(mapPath));
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	this->addPixmap(bg);

	RiskMap* map = this->driver->getRiskMap();
	for (auto const &ent1 : map->getCountries()) {
		const Country& country = ent1.second;
		QGraphicsCountryItem* item = new QGraphicsCountryItem(map->getCountry(country.getName()));
		if (this->editable) {
			item->setFlag(QGraphicsItem::ItemIsMovable);
		}
		item->setPos(country.getPositionX(), country.getPositionY());
		this->addItem(item);
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
		connectNeighboursVisit(visited, country);
	}
}

/**
 * @brief Helper method of repopulate() that implements DFS on the RiskMap's countries.
 */
void MapScene::connectNeighboursVisit(std::map<const std::string, bool>& visited, Country* country) {
	QPen pen(QColor(0xFF, 0, 0, 0x40));
	pen.setWidth(1);

	bool& was_visited = visited.at(country->getName());
	if (was_visited) {
		return;
	}
	was_visited = true;

	RiskMap* map = this->driver->getRiskMap();
	for (auto const &neighbour_str : map->getNeighbours(country->getName())) {
		Country* neighbour = map->getCountry(neighbour_str);
		QGraphicsCountryEdgeItem* line = new QGraphicsCountryEdgeItem(country, neighbour);
		this->addItem(line);
		line->setZValue(1);
		connectNeighboursVisit(visited, neighbour);
	}
}
