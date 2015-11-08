#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "player.h"
#include "player_view.h"
#include "playerinfowidget.h"

MainScreen::MainScreen(RiskMap *map, QWidget *parent) :QMainWindow(parent), ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    nameDialog = new PlayerNameDialog(this);
    this->map = map;
	setupPlayers();
    setMouseTracking(true);
    ui->attackRadio->setChecked(true);

//    Player* test = new Player("test");
//	test->setBattlesWon(10);
//	test->setReinforcements(3513);
//	test->setTotalArmy(534);
//	PlayerView* pv = new PlayerView(test);
//	PlayerInfoWidget* playerInfoWidget = new PlayerInfoWidget(this,pv);
//	ui->horizontalLayout_2->addWidget(playerInfoWidget);

}

void MainScreen::setupPlayers(){
	std::unordered_map<std::string,Player>::iterator playerIterator;
	std::unordered_map<std::string,Player> players = map->getPlayers();
	for(playerIterator = players.begin(); playerIterator != players.end(); playerIterator++){
		PlayerView *pv =  new PlayerView(&(playerIterator->second));
		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this,pv);
		ui->horizontalLayout_2->addWidget(playerinfo);
	}
}

void MainScreen::mousePressEvent(QMouseEvent *e){
    qDebug() <<e->pos().x();
}

void MainScreen::addPlayerView(QWidget *pvWidget)
{
    ui->verticalLayout_2->addWidget(pvWidget);
}

MainScreen::~MainScreen()
{
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
