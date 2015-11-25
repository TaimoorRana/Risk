#include <functional>
#include <random>
#include <time.h>
#include <set>

#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>

#include "debug.h"
#include "game_driver.h"
#include "game_state.h"
#include "mainscreen.h"
#include "map_scene.h"
#include "map_renderer.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"

#include "logscreen.h"



MainScreen::MainScreen(RiskMap *map, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	this->map = map;
	map->attachObserver(this);
	GameDriver::getInstance()->attachObserver(this);

	this->scene = new MapScene(map, this);
	ui->graphicsView->setScene(scene);
	ui->reinforcementLabel->setEnabled(true);
}

MainScreen::~MainScreen() {
	map->detachObserver(this);
	GameDriver::getInstance()->detachObserver(this);
	delete editor;
	delete scene;
	delete ui;
}

bool MainScreen::setupPlayers() {
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
			errorDialog.setText("File not found");
			errorDialog.setDetailedText("Please choose a file that exists, with the .map and .bmp files named the same and in the same folder.");
			errorDialog.exec();
			continue;
		}

		this->map->parse(this->mapPath);
		if (!this->map->validate()) {
			QMessageBox errorDialog(this);
			errorDialog.setWindowTitle("Error!");
			errorDialog.setText("Invalid map");
			errorDialog.setDetailedText("The map did not validate. Please contact its author.");
			errorDialog.exec();
			continue;
		}

		valid = true;
	}

	this->map->setNotificationsEnabled(false);

	int totalPlayers = dialog.getPlayerCount();
	for (int x = 0; x < totalPlayers; x++) {
		this->map->addPlayer(Player("Player " + std::to_string(x+1)));
	}

	GameDriver* driver = GameDriver::getInstance();
	std::string firstPlayerName = (*this->map->getPlayers().begin()).first;
	driver->setCurrentPlayerName(firstPlayerName);

	this->map->setNotificationsEnabled(true);
	this->map->notifyObservers();

	// Assign random countries to players in a round-robin fashion
	std::vector<Country*> vectorOfCountryPointers;
	for (auto const &ent1 : this->map->getCountries()) {
		const Country& ctmp = ent1.second;
		vectorOfCountryPointers.push_back(this->map->getCountry(ctmp.getName()));
	}

	std::vector<int> x = getVectorOfIndicesRandomCountryAccess(this->map->getCountries().size());
	std::vector<int>::const_iterator iter = x.begin();
	int p=0;
	while (iter != x.end()){
		Country* country = vectorOfCountryPointers[*iter];
		Player* player = playerRoundRobin(p++);
		country->setPlayer(player->getName());
		player->addCountry(country->getName());
		country->setArmies(10);
		iter++;
	}

	this->setReinforcements();
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
	auto iter = this->map->getPlayers().begin();
	std::advance(iter, i % (this->map->getPlayers().size()));
	return this->map->getPlayer((*iter).first);
}

void MainScreen::setReinforcements()
{
	for(auto const &ent1: map->getPlayers()){
		Player p = ent1.second;
		Player *player = map->getPlayer(p.getName());
		player->setTotalArmy(player->getCountriesOwned().size()*2);
		std::set<std::string> continents =player->getContinentsOwned();
		std::set<std::string>::iterator itContinents = continents.begin();
		int reinforcementArmies = 0;
		//gets the reinforcement armies based if they have more than 9 countries

		if (player->getCountriesOwned().size()>9){
			reinforcementArmies = player->getCountriesOwned().size()/3;
		}
		else {
			reinforcementArmies = 3;
		}
		while (itContinents!= continents.end()){
			reinforcementArmies += map->getContinentByName(*itContinents)->getReinforcementBonus();
		}
		player->setReinforcements(reinforcementArmies);

		player->notifyObservers();

	}
}

void MainScreen::on_endPhasePushButton_clicked() {
	this->endPhase();
}

void MainScreen::endPhase()
{
	GameDriver* driver = GameDriver::getInstance();

	Mode currentMode = driver->getCurrentMode();
	if (currentMode == REINFORCEMENTMODE) {
		driver->setCurrentMode(ATTACKMODE);
	}
	else if (currentMode == ATTACKMODE) {
		driver->setCurrentMode(FORTIFICATIONMODE);
	}
	else {
		this->nextTurn();
	}
	debug("End Phase");

	for(auto const &ent1: map->getPlayers()){
		Player p = ent1.second;
		Player *player = map->getPlayer(p.getName());
		player->notifyObservers();
		debug(""+player->getName()+" owns "+ std::to_string(player->getCountriesOwned().size())+ " countries and "+ std::to_string(player->getTotalArmy())+ " armies.");
	}
}


void MainScreen::on_logButton_clicked()
{
	if(logSelector !=NULL){
		this->logSelector->show();
		this->logSelector->raise();
	}
	else{
		this->logSelector = new LogSelector(this,(this->map->getPlayers().size()));
		this->logSelector->show();
	}
	bool decision=true;
	while (decision) {

		LogScreen *lScreen = new LogScreen(this);
		lScreen->setPlayers(logSelector->getSelectedPlayer());
		lScreen->setState(logSelector->getSelectedPhase());
		if(this->logSelector->exec()){

			lScreen->show();

			decision =false;
		}
		else if(this->logSelector->close()){
			decision = false;
		}
	}

}


void MainScreen::on_loadAction_triggered() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open saved game"), QDir::currentPath(), tr("Risk game state (*.risksave)")));
	this->raise();
	if (filename.length() > 0) {
		GameState::load(filename.toStdString(), GameDriver::getInstance(), this->map);
	}

}



void MainScreen::on_saveAction_triggered() {
	QString filename(QFileDialog::getSaveFileName(this, tr("Save game"), QDir::currentPath(), tr("Risk game state (*.risksave)")));
	this->raise();
	if (filename.length() > 0) {
		GameState::save(filename.toStdString(), GameDriver::getInstance(), this->map);
	}
}

void MainScreen::on_mapEditorAction_triggered() {
	if (editor != NULL) {
		this->editor->show();
		this->editor->raise();
	}
	else {
		this->editor = new MapEditor(this);
		this->editor->show();
	}

}

void MainScreen::observedUpdated() {
	MapRenderer::updateScene(this->map, this->scene, this->mapPath, false);

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

		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this, player, this->scene);
		ui->horizontalLayout_2->addWidget(playerinfo);
	}

	// Handle observe notify event from GameDriver: setup current game mode
	GameDriver* driver = GameDriver::getInstance();
	Mode mode = driver->getCurrentMode();
	ui->reinforcementLabel->setEnabled(mode == REINFORCEMENTMODE);
	ui->attackLabel->setEnabled(mode == ATTACKMODE);
	ui->fortifyLabel->setEnabled(mode == FORTIFICATIONMODE);
}

void MainScreen::nextTurn()
{
	GameDriver* driver = GameDriver::getInstance();
	auto iterator = this->map->getPlayers().find(driver->getCurrentPlayerName());
	auto end = this->map->getPlayers().end();
	std::advance(iterator, 1);
	if (iterator == end) {
		iterator = this->map->getPlayers().begin();
	}
	driver->setCurrentPlayerName((*iterator).first);
	driver->setCurrentMode(REINFORCEMENTMODE);
}

