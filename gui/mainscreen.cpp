#include <functional>
#include <random>
#include <time.h>
#include <set>

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
#include "debug.h"

MainScreen::MainScreen(RiskMap *map, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	this->map = map;
	map->attachObserver(this);

	this->scene = new MapScene(map, this);
	ui->graphicsView->setScene(scene);
    initializeMode();
}

void MainScreen::initializeMode(){
    ui->reinforcementLabel->setEnabled(true);
    currentMode = REINFORCEMENTMODE;
    reinforceModeCompleted = true;
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
    totalPlayers = dialog.getPlayerCount();
	Player* player = nullptr;
	for (int x = 0; x < totalPlayers; x++) {
		player = map->addPlayer(Player("Player " + std::to_string(x+1)));
		if(x == 0){
			currentPLayerName = "Player " + std::to_string(x+1);
		}
		players.push_back("Player " + std::to_string(x+1));
		player->setNotificationsEnabled(false);
		PlayerInfoWidget* playerinfo = new PlayerInfoWidget(this, player, this->scene);
		ui->horizontalLayout_2->addWidget(playerinfo);
		player->setTotalArmy(22);
		player->setReinforcements(10);
		player->setNotificationsEnabled(true);
		player->notifyObservers();
	}
	this->map->notifyObservers();


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
        debug("Setting "+country->getName()+" to "+ player->getName());
        country->setPlayer(player->getName());
        player->addCountry(country->getName());
		country->setArmies(10);
        iter++;
    }


    setReinforcements();

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
    std::unordered_map<std::string, Player>::const_iterator iter = this->map->getPlayers().begin();
    std::advance(iter,i % (this->map->getPlayers().size()));
    return this->map->getPlayer((*iter).first);
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

		player->notifyObservers();

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
    startGame();
    if(ui->reinforcementLabel->isEnabled()){
        ui->reinforcementLabel->setEnabled(false);
        ui->attackLabel->setEnabled(true);
        ui->fortifyLabel->setEnabled(false);

		currentMode = ATTACKMODE;
        attackModeCompleted = true;
    }else if(ui->attackLabel->isEnabled()){
        ui->reinforcementLabel->setEnabled(false);
        ui->attackLabel->setEnabled(false);
        ui->fortifyLabel->setEnabled(true);

		currentMode = FORTIFICATIONMODE;
        fortificationModeCompleted = true;
	}else{
        ui->reinforcementLabel->setEnabled(true);
        ui->attackLabel->setEnabled(false);
        ui->fortifyLabel->setEnabled(false);

		currentMode = REINFORCEMENTMODE;
        reinforceModeCompleted = true;
	}
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

void MainScreen::startGame()
{
		if(attackModeCompleted == true && reinforceModeCompleted == true && fortificationModeCompleted == true){
			currentPlayer++;
            if(currentPlayer >= totalPlayers){
                currentPlayer = 0;
            }
			currentPLayerName = players[currentPlayer];
			attackModeCompleted = false;
			reinforceModeCompleted = false;
			fortificationModeCompleted = false;
		}
}

