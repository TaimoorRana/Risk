#include <functional>
#include <random>

#include <QMessageBox>
#include <time.h>
#include "mainscreen.h"
#include "map_scene.h"
#include "map_renderer.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"


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
	if(dialog.exec() == QDialog::Rejected)
	{
		qDebug("Quitting");
		return false;
	}

	this->playerName = dialog.getPlayerName();
	this->CPUs = dialog.getAIPlayerCount();
	this->mapPath = dialog.getMapPath();
	this->map->parse(this->mapPath);
	if (!this->map->validate()) {
		QMessageBox errorDialog(this);
		errorDialog.setWindowTitle("Error!");
		errorDialog.setText("Invalid map");
		errorDialog.setDetailedText("The map did not validate. Please contact its author.");
		errorDialog.exec();
		this->close();
	}

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

	setupPlayer();
	setupCPUs();
	return true;
}

void MainScreen::setupPlayer()
{
	for(auto const &ent1: map->getPlayers()){
		Player p = ent1.second;
		Player *player = map->getPlayer(p.getName());
		player->setTotalArmy(22);
		player->setReinforcements(10);
		player->notifyObserver();
		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this, player, this->scene);
		ui->horizontalLayout_2->addWidget(playerinfo);
	}
}

void MainScreen::setupCPUs()
{
	for(int x = 0; x < CPUs; x++){
		Player* cpu = new Player("CPU");
		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this,cpu);
		ui->horizontalLayout_2->addWidget(playerinfo);
		map->addPlayer(*cpu);
	}
}

void MainScreen::addPlayerView(QWidget *pvWidget)
{
	ui->verticalLayout_2->addWidget(pvWidget);
}

void MainScreen::setCPUs(int total)
{
	this->CPUs = total;
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
}

Mode MainScreen::getCurrentMode(){
	return currentMode;
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
