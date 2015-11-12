#include <functional>
#include <random>
#include <time.h>

#include <QMessageBox>
#include <QFileInfo>
#include <QString>

#include "mainscreen.h"
#include "map_scene.h"
#include "map_renderer.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"
#include "gamedriver.h"


MainScreen::MainScreen(RiskMap *map, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	this->map = map;
	map->attachObserver(this);

	this->scene = new MapScene(map, this);
	ui->graphicsView->setScene(scene);
	ui->reinforcementRadio->setChecked(true);
	currentMode = REINFORCEMENTMODE;
}

MainScreen::~MainScreen() {
	map->detachObserver(this);
	delete editor;
	delete scene;
	delete ui;
}

bool MainScreen::setupPlayers(){
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

	Player* player = nullptr;
	for (int x = 0; x < dialog.getPlayerCount(); x++) {
		player = map->addPlayer(Player("Player " + std::to_string(x+1)));
		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this, player, this->scene);
		player->setTotalArmy(22);
		player->setReinforcements(10);
		ui->horizontalLayout_2->addWidget(playerinfo);
		player->notifyObserver();
	}
	this->map->notifyObservers();

	std::mt19937::result_type seed = time(0);
	auto player_rand = std::bind(std::uniform_int_distribution<int>(0, this->map->getPlayers().size()-1), std::mt19937(seed));
	for (auto const &ent1 : this->map->getCountries()) {
		// FIXME: We should really just not make these const.
		const Country& ctmp = ent1.second;
		Country* country = this->map->getCountry(ctmp.getName());
		// Set random player
		auto it = this->map->getPlayers().begin();
		std::advance(it, player_rand());
		const Player& ptmp = it->second;
		Player* player = this->map->getPlayer(ptmp.getName());
		country->setPlayer(player->getName());
		// Set 2 armies
		player->addCountry(country->getName());
		country->setArmies(2);
	}
	setReinforcements();

	return true;
}


void MainScreen::setReinforcements()
{
	for(auto const &ent1: map->getPlayers()){
		Player p = ent1.second;
		Player *player = map->getPlayer(p.getName());
		player->setTotalArmy(player->getCountriesOwned().size()*2);
		set<string> continents =player->getContinentsOwned();
		set<string>::iterator itContinents = continents.begin();
		int reinforcementArmies=0;
		//gets the reinforcement armies based if they have more than 9 countries

		if(player->getCountriesOwned().size()>9){
			reinforcementArmies = player->getCountriesOwned().size()/3;
		}
		else{
			reinforcementArmies = 3;
		}
		while(itContinents!= continents.end()){
			reinforcementArmies += map->getContinent(*itContinents)->getReinforcementBonus();
		}
		player->setReinforcements(reinforcementArmies);

		player->notifyObserver();

	}
}




void MainScreen::addPlayerView(QWidget *pvWidget)
{
	ui->verticalLayout_2->addWidget(pvWidget);
}



void MainScreen::setCurrentMode(Mode newMode)
{
	this->currentMode = newMode;
}


void MainScreen::on_pushButton_clicked()
{
	if(ui->reinforcementRadio->isChecked()){
		ui->attackRadio->setChecked(true);
		currentMode = ATTACKMODE;
		return;
	}else if(ui->attackRadio->isChecked()){
		ui->fortifyRadio->setChecked(true);
		currentMode = FORTIFICATIONMODE;
		return;
	}else{
		ui->reinforcementRadio->setChecked(true);
		currentMode = REINFORCEMENTMODE;
		return;
	}

	GameDriver* driver = GameDriver::getInstance();
	driver->startGame();
}

void MainScreen::endPhase()
{
	on_pushButton_clicked();

}

Mode MainScreen::getCurrentMode(){
	return currentMode;
}

void MainScreen::setCurrentPlayer(std::string name)
{
	this->currentPLayerName = name;
}

std::string MainScreen::getCurrentPlayer()
{
	return this->currentPLayerName;
}

/**
 * Callback to handle user selecting File > Map Editor.
 */
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
}
