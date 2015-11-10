#include <QDebug>

#include "mainscreen.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"

MainScreen::MainScreen(RiskMap *map, QWidget *parent) :QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	nameDialog = new PlayerNameDialog(this);
	this->map = map;
	setMouseTracking(true);
	ui->attackRadio->setChecked(true);
}

void MainScreen::setupPlayers(){
	setupPlayer();
	setupCPUs();
}

void MainScreen::setupPlayer()
{
	Player* player = new Player(this->playerName.toStdString());
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

void MainScreen::mousePressEvent(QMouseEvent *e){
		qDebug() <<e->pos().x();
}

void MainScreen::addPlayerView(QWidget *pvWidget)
{
	ui->verticalLayout_2->addWidget(pvWidget);
}

void MainScreen::setCPUs(int total)
{
	this->CPUs = total;
}

void MainScreen::setPLayerName(QString name)
{
	this->playerName = name;
}

MainScreen::~MainScreen()
{
	delete nameDialog;
	delete editor;
	delete ui;
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
