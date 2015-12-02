#include <algorithm>
#include <functional>
#include <random>
#include <time.h>
#include <set>

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>

#include "info_widgets/continent_info_widget.h"
#include "info_widgets/info_widget.h"
#include "info_widgets/reinforcement_info_widget.h"
#include "game_driver.h"
#include "game_state.h"
#include "log_selector.h"
#include "mainscreen.h"
#include "map_scene.h"
#include "player.h"
#include "playernamedialog.h"
#include "cards_trade_dialog.h"

MainScreen::MainScreen(GameDriver* driver, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	this->driver = driver;
	this->driver->attachObserver(this);
	this->driver->getRiskMap()->attachObserver(this);

	this->scene = new MapScene(this->driver, this);
	ui->graphicsView->setScene(scene);
	ui->reinforcementLabel->setEnabled(true);

    ui->useCardsButton->setFlat(true);
    ui->useCardsButton->setAutoFillBackground(true);
    ui->useCardsButton->setIcon(QIcon(":cards.png"));
    ui->useCardsButton->setIconSize(QSize(50,50));
    ui->useCardsButton->setToolTip("Trade your cards");
    ui->useCardsButton->setMaximumHeight(40);

    ui->logButton->setFlat(true);
    ui->logButton->setAutoFillBackground(true);
    ui->logButton->setIcon(QIcon(":log.png"));
    ui->logButton->setIconSize(QSize(40,40));
    ui->logButton->setToolTip("Display game log");
    ui->logButton->setMaximumHeight(40);
}

MainScreen::~MainScreen() {
	this->driver->detachObserver(this);
	this->driver->getRiskMap()->detachObserver(this);
	delete editor;
	delete scene;
	delete ui;
}

bool MainScreen::setupPlayers() {
	RiskMap* map = this->driver->getRiskMap();
	PlayerNameDialog dialog(this);
	bool valid = false;
	while (!valid) {
		if (dialog.exec() == QDialog::Rejected) {
			exit(0);
		}
		this->mapPath = dialog.getMapPath();
		QFileInfo mapFile(QString::fromStdString(this->mapPath));
		if (!mapFile.exists()) {
			QMessageBox errorDialog(this);
			errorDialog.setWindowTitle("Error!");
			errorDialog.setText("File not found. Please choose a file that exists, with the .map and .bmp files named the same and in the same folder.");
			errorDialog.exec();
			continue;
		}

		map->load(this->mapPath);
		if (!map->validate()) {
			QMessageBox errorDialog(this);
			errorDialog.setWindowTitle("Error!");
			errorDialog.setText("Invalid map: the map did not validate. Please contact its author.");
			errorDialog.exec();
			continue;
		}

		valid = true;
	}

	map->setNotificationsEnabled(false);

	// Setup the number of selected human players
	int humanPlayers = dialog.getPlayerCount();
	for (int x = 1; x <= humanPlayers; x++) {
		Player *player = map->addPlayer(Player("Player " + std::to_string(x)));
		player->notifyObservers();
		player->updateCards(10);
	}

	// Future improvement: make this selectable from the UI
	int cpuPlayers = 1;
	for (int x = humanPlayers+1; x <= humanPlayers+cpuPlayers; x++) {
		Player *player = map->addPlayer(Player("Player " + std::to_string(x) + " (AI)"));
		player->setNotificationsEnabled(false);
		player->setHuman(false);
		player->setNotificationsEnabled(true);
		player->notifyObservers();
	}

	// Determine the player who starts the game
	std::string firstPlayerName = (*map->getPlayers().begin()).first;
	this->driver->setCurrentPlayerName(firstPlayerName);

	map->setNotificationsEnabled(true);
	map->notifyObservers();

	// Assign random countries to players in a round-robin fashion
	std::vector<Country*> availableCountries;
	for (auto const &ent1 : map->getCountries()) {
		const Country& ctmp = ent1.second;
		availableCountries.push_back(map->getCountry(ctmp.getName()));
	}

	// Randomize order of country pointer list
	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(availableCountries), std::end(availableCountries), engine);

	// Assign countries round-robin
	auto playerIter = map->getPlayers().begin();
	for (Country* country : availableCountries) {
		const Player& player = (*playerIter).second;
		country->setPlayer(player.getName());

		std::advance(playerIter, 1);
		if (playerIter == map->getPlayers().end()) {
			playerIter = map->getPlayers().begin();
		}
	}

	// Calculate player reinforcements now that countries are assigned
	this->driver->recalculateReinforcements();

	// Distribute the other armies
	for (auto const &iter : map->getPlayers()){
		this->allocateArmiesByNumberOfPlayers(iter.first);
	}

	return true;
}

void MainScreen::allocateArmiesByNumberOfPlayers(const std::string playerName){
	RiskMap* map = this->driver->getRiskMap();
	const int armiesByNumPlayers[] = {40, 35, 30, 25, 20};
	int totalArmies = armiesByNumPlayers[map->getPlayers().size()-2];

	// Create a vector of country pointers for countries the player owns
	std::vector<Country*> playerCountries;
	for (auto const &countryName : map->getCountriesOwnedByPlayer(playerName)) {
		playerCountries.push_back(map->getCountry(countryName));
	}

	// Randomize order of country pointer list
	auto engine = std::default_random_engine{};
	std::shuffle(std::begin(playerCountries), std::end(playerCountries), engine);

	auto playerCountriesIter = playerCountries.begin();
	while (totalArmies > 0) {
		Country* country = *playerCountriesIter;
		country->addArmies(1);
		totalArmies--;
		std::advance(playerCountriesIter, 1);
		if (playerCountriesIter == playerCountries.end()) {
			playerCountriesIter = playerCountries.begin();
		}
	}

	// Signal to update the info widgets.
	for (auto &ent1: map->getPlayers()){
		map->getPlayer(ent1.first)->notifyObservers();
	}
}

void MainScreen::on_endPhasePushButton_clicked() {
	if (this->driver->getCurrentMode() == FORTIFICATION) {
		ui->useCardsButton->setEnabled(true);
	}
	this->driver->endPhase();
}

void MainScreen::on_logButton_clicked()
{
	std::vector<std::string> playerNames = std::vector<std::string>();
	for (auto &ent1 : this->driver->getRiskMap()->getPlayers()) {
		std::string playerName = ent1.first;
		playerNames.push_back(playerName);
	}
	LogSelector* logSelector = new LogSelector(playerNames, this);
	if (logSelector->exec() == QDialog::Accepted) {
		std::string logPhase = logSelector->getSelectedPhase();
		std::string logPlayer = logSelector->getSelectedPlayer();
		if (this->logScreen != nullptr) {
			delete logScreen;
		}
		this->logScreen = new LogScreen(this->driver, logPhase, logPlayer, this);
		this->logScreen->show();
	}
	delete logSelector;
}

void MainScreen::on_useCardsButton_clicked()
{
	if (this->driver->getRiskMap()->getPlayer(driver->getCurrentPlayerName())->getCards() >= 2)
	{
		CardsTradeDialog* cardsTradeDialog = new CardsTradeDialog(this->driver, this);
		if (cardsTradeDialog->exec() == QDialog::Accepted) {
			ui->useCardsButton->setEnabled(false);
		}
	} else
	{
		QMessageBox errorDialog(this);
		errorDialog.setWindowTitle("Insufficient Number of Cards");
		errorDialog.setText("You need at least 2 cards to be able to trade!");
		errorDialog.exec();
	}
}

void MainScreen::on_loadAction_triggered() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open saved game"), QDir::currentPath(), tr("Risk game state (*.risksave)")));
	this->raise();
	if (filename.length() > 0) {
		GameState::load(filename.toStdString(), this->driver);
	}
}

void MainScreen::on_saveAction_triggered() {
	QString filename(QFileDialog::getSaveFileName(this, tr("Save game"), QDir::currentPath(), tr("Risk game state (*.risksave)")));
	this->raise();
	if (filename.length() > 0) {
		GameState::save(filename.toStdString(), this->driver);
	}
}

void MainScreen::on_mapEditorAction_triggered() {
	if (editor != nullptr) {
		this->editor->show();
		this->editor->raise();
	}
	else {
		this->editor = new MapEditor(this);
		this->editor->show();
	}
}

void MainScreen::observedUpdated() {
	RiskMap* map = this->driver->getRiskMap();
	std::string currentPlayerName = this->driver->getCurrentPlayerName();

	// Verify victory conditions
	if (this->driver->hasWon(currentPlayerName)) {
		QMessageBox winnerDialog(this);
		winnerDialog.setWindowTitle("Game has concluded");
		winnerDialog.setText(QString("%1 has won the game!").arg(QString::fromStdString(currentPlayerName)));
		winnerDialog.exec();
		this->close();
	}

	this->scene->repopulate(this->mapPath);

	// Handle observe notify event from map: clear existing player info widgets
	QLayoutItem *layoutItem;
	while (ui->horizontalLayout_2->count() > 0) {
		layoutItem = ui->horizontalLayout_2->takeAt(0);
		delete layoutItem->widget();
		delete layoutItem;
	}
	// Instantiate new player info widgets for active each player
	for (auto const &ent1: map->getPlayers()) {
		Player p = ent1.second;
		Player *player = map->getPlayer(p.getName());

		IInfoWidget* playerinfo = new InfoWidget(player, this->scene, ui->horizontalLayout_2->widget());
		ui->horizontalLayout_2->addWidget(playerinfo);
	}

	// Handle observe notify event from GameDriver: setup current game mode
	Mode mode = this->driver->getCurrentMode();
	ui->reinforcementLabel->setEnabled(mode == REINFORCEMENT);
	ui->attackLabel->setEnabled(mode == ATTACK);
	ui->fortifyLabel->setEnabled(mode == FORTIFICATION);
}

