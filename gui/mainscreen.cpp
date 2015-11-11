#include <QDebug>

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

	setMouseTracking(true);
	ui->attackRadio->setChecked(true);
}

MainScreen::~MainScreen() {
	map->detachObserver(this);
	delete editor;
	delete scene;
	delete ui;
}

void MainScreen::setupPlayers(){
	PlayerNameDialog dialog(this);
	dialog.exec();

	this->playerName = dialog.getPlayerName();
	this->CPUs = dialog.getAIPlayerCount();
	this->mapPath = dialog.getMapPath();
	this->map->parse(this->mapPath);

	setupPlayer();
	setupCPUs();
}

void MainScreen::setupPlayer()
{
	Player* player = new Player(this->playerName);
	PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this,player);
	ui->horizontalLayout_2->addWidget(playerinfo);
	map->addPlayer(*player);
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
		if(ui->attackRadio->isChecked()){
			ui->fortifyRadio->setChecked(true);
			return;
		}else if(ui->fortifyRadio->isChecked()){
			ui->reinforcementRadio->setChecked(true);
			return;
		}else{
			ui->attackRadio->setChecked(true);
			return;
		}
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
