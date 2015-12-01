#include <functional>
#include <random>
#include <time.h>
#include <set>

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

MainScreen::MainScreen(GameDriver* driver, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	this->driver = driver;
	this->driver->attachObserver(this);
	this->driver->getRiskMap()->attachObserver(this);

	this->scene = new MapScene(this->driver, this);
	ui->graphicsView->setScene(scene);
	ui->reinforcementLabel->setEnabled(true);
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

	int totalPlayers = dialog.getPlayerCount();
	for (int x = 0; x < totalPlayers-1; x++) {
		Player *player = map->addPlayer(Player("Player " + std::to_string(x+1)));
		player->setNotificationsEnabled(false);
		player->setReinforcements(10);
		player->setNotificationsEnabled(true);
		player->notifyObservers();
	}

	Player *player = map->addPlayer((Player("Player machine" )));
	player->setNotificationsEnabled(false);
	player->setHuman(false);
	player->setReinforcements(10);
	player->setNotificationsEnabled(true);
	player->notifyObservers();
	std::string firstPlayerName = (*map->getPlayers().begin()).first;
	this->driver->setCurrentPlayerName(firstPlayerName);

	map->setNotificationsEnabled(true);
	map->notifyObservers();

	// Assign random countries to players in a round-robin fashion
	std::vector<Country*> vectorOfCountryPointers;
	for (auto const &ent1 : map->getCountries()) {
		const Country& ctmp = ent1.second;
		vectorOfCountryPointers.push_back(map->getCountry(ctmp.getName()));
	}

	std::vector<int> x = getVectorOfIndicesRandomCountryAccess(this->driver->getRiskMap()->getCountries().size());
	std::vector<int>::const_iterator iter = x.begin();
	int p=0;
	while (iter != x.end()){
		Country* country = vectorOfCountryPointers[*iter];
		Player* player = playerRoundRobin(p++);
		country->setPlayer(player->getName());
		country->setArmies(1);
		iter++;
	}
	this->driver->recalculateReinforcements();

	// distribute the rest of the armies
	for(auto const &iter : map->getPlayers()){
		this->allocateArmiesByNumberOfPlayers(iter.first);
	}

	return true;
}

std::vector<int> MainScreen::getVectorOfIndicesRandomCountryAccess(int nCountries){
	std::set<int> s;
	std::vector<int> v;

	std::mt19937::result_type seed = time(0);

	auto countryRand = std::bind(std::uniform_int_distribution<int>(0, nCountries-1), std::mt19937(seed));
	int nextRand;

	while (s.size() < nCountries){
		nextRand = countryRand();
		if (s.find(nextRand) == s.end()){
			v.push_back(nextRand);
			s.insert(nextRand);
		}
	}
	return v;
}

Player* MainScreen::playerRoundRobin(int i){
	RiskMap* map = this->driver->getRiskMap();
	auto iter = map->getPlayers().begin();
	std::advance(iter, i % (map->getPlayers().size()));
	return map->getPlayer((*iter).first);
}

void MainScreen::allocateArmiesByNumberOfPlayers(const std::string p){
	RiskMap* map = this->driver->getRiskMap();
	const int armiesByNumPlayers[] = {40, 35, 30, 25, 20};
	int totalArmies = armiesByNumPlayers[map->getPlayers().size()-2];

	std::vector<Country*> vectorOfCountryPointers;
	for (auto const &ent1 : map->getCountriesOwnedByPlayer(p)) {
		vectorOfCountryPointers.push_back(map->getCountry(ent1));
	}

	totalArmies -= map->getCountriesOwnedByPlayer(p).size();

	std::vector<int> x = getVectorOfIndicesRandomCountryAccess(map->getCountriesOwnedByPlayer(p).size());
	std::vector<int>::const_iterator iter = x.begin();

	while (totalArmies > 0){
		Country* country = vectorOfCountryPointers[*iter];
		country->addArmies(1);
		totalArmies--;
		if (++iter == x.end()) {
			iter = x.begin();
		}
	}
	
	for(auto &ent1: map->getPlayers()){
		map->getPlayer(ent1.first)->notifyObservers();
	}
	
}

void MainScreen::on_endPhasePushButton_clicked() {
	this->endPhase();
}

void MainScreen::endPhase()
{
	Mode currentMode = this->driver->getCurrentMode();
	if (currentMode == REINFORCEMENT) {
		driver->setCurrentMode(ATTACK);
	}
	else if (currentMode == ATTACK) {
		driver->setCurrentMode(FORTIFICATION);
	}
	else {
		this->nextTurn();
	}
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

void MainScreen::nextTurn()
{
	RiskMap* map = this->driver->getRiskMap();
	auto iterator = map->getPlayers().find(this->driver->getCurrentPlayerName());
	auto end = map->getPlayers().end();
	std::advance(iterator, 1);
	if (iterator == end) {
		iterator = map->getPlayers().begin();
	}
	this->driver->setCurrentPlayerName((*iterator).first);
	this->driver->setCurrentMode(REINFORCEMENT);
}
