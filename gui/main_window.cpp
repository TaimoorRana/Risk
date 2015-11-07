#include <QDir>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <random>
#include <functional>
#include <time.h>

#include "debug.h"
#include "main_window.h"
#include "ui_main_window.h"
#include <QMouseEvent>
#include <qdebug.h>

MainWindow::MainWindow(RiskMap* map, QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MainWindow;
	ui->setupUi(this);
	observedMap = map;
	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);
    setMouseTracking(true);
    tool = OFF;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    switch(tool){
        case ADDCOUNTRY:
            int xpos =  event->pos().x();
            int ypos =  event->pos().y();
            qDebug()<< xpos;
            qDebug()<< ypos;
            QRectF r1(xpos-10-98,ypos-10-125,20,20);
            QPen p(QColor(13,145,67,255));
            scene->addEllipse(r1,p,QBrush());
            break;
        case REMCOUNTRY:
            
            break;
    }
}

MainWindow::~MainWindow() {
	scene->clear();
	delete scene;
	delete ui;
}

bool MainWindow::validateFilename(const QString& text) {
	QFileInfo mapFile(text);
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	return mapFile.exists() && bmpFile.exists();
}

void MainWindow::on_filenameLineEdit_textChanged(QString text) {
	if (this->validateFilename(text)) {
		ui->loadPushButton->setEnabled(true);
	}
	else {
		ui->loadPushButton->setEnabled(false);
	}
}

void MainWindow::on_browsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk map files (*.map)")));
	ui->filenameLineEdit->setText(filename);
}

void MainWindow::on_loadPushButton_clicked() {
	observedMap->parse(ui->filenameLineEdit->text().toStdString());
}

// void MainWindow::on_randOwnerPushButton_clicked() {
// 	std::mt19937::result_type seed = time(0);
// 	auto player_rand = std::bind(std::uniform_int_distribution<int>(0, observedMap->getPlayers().size()-1), std::mt19937(seed));
//
// 	for (auto const &ent1 : observedMap->getCountries()) {
// 		const Country& country = ent1.second;
//
// 		auto it = observedMap->getPlayers().begin();
// 		std::advance(it, player_rand());
// 		const Player& player = it->second;
// 		Country* mutableCountry = observedMap->getCountry(country.getName());
// 		mutableCountry->setPlayer(player.getName());
// 	}
// }

// void MainWindow::on_randArmiesPushButton_clicked() {
// 	for (auto const &ent1 : observedMap->getCountries()) {
// 		const Country& country = ent1.second;
// 		Country* mutableCountry = observedMap->getCountry(country.getName());
//         mutableCountry->setArmies((rand() % 10) + 1);
// 	}
// }

void MainWindow::on_saveMapPushButton_clicked(){
    debug("Save Button clicked\n");
}

void MainWindow::on_addCountryPushButton_clicked(){
	debug("Add Country");
    tool = ADDCOUNTRY;
}

void MainWindow::on_removeCountryPushButton_clicked(){
    debug("Remove Country");
    tool = REMCOUNTRY;
}

void MainWindow::on_addNeighbourPushButton_clicked(){
    debug("Add Neighbour");
    tool = ADDLINK;
}

void MainWindow::on_removeNeighbourPushButton_clicked(){
    debug("Remove Neighbour");
    tool = REMLINK;
}

void MainWindow::observedUpdated() {
	scene->clear();

	debug("render event");

	QFileInfo mapFile(ui->filenameLineEdit->text());
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	scene->addPixmap(bg);

	int diameter = 0;
	QFont font("Verdana", 10);

	std::mt19937::result_type seed = 4;
	auto color_rand = std::bind(std::uniform_int_distribution<int>(0, 255), std::mt19937(seed));

	std::map<const std::string, QColor> continentPalette = std::map<const std::string, QColor>();
	for (auto const &ent1 : observedMap->getContinents()) {
		const Continent& continent = ent1.second;
		continentPalette.insert(std::pair<const std::string, QColor>(continent.getName(), QColor(color_rand(), color_rand(), color_rand())));
	}

	std::map<std::string, QColor> playerPalette = std::map<std::string, QColor>();
	for (auto const &ent1 : observedMap->getPlayers()) {
		const Player& player = ent1.second;
		playerPalette.insert(std::pair<std::string, QColor>(player.getName(), QColor(color_rand(), color_rand(), color_rand())));
	}
	playerPalette.insert(std::pair<const std::string, QColor>("", QColor(204, 204, 204)));

	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;

		diameter = 30;
		Continent* continent = observedMap->getContinentOfCountry(country.getName());
		QColor continentColor(continentPalette.at(continent->getName()));
		QGraphicsEllipseItem* ellipse = scene->addEllipse(country.getPositionX()-diameter/2, country.getPositionY() - diameter/2, diameter, diameter, QPen(), QBrush(continentColor));
		ellipse->setZValue(1);

		diameter = 15;
		QColor playerColor(playerPalette.at(country.getPlayer()));
		ellipse = scene->addEllipse(country.getPositionX()-diameter/2, country.getPositionY() - diameter/2, diameter, diameter, QPen(), QBrush(playerColor));
		ellipse->setZValue(2);

		Player* owner = observedMap->getPlayer(country.getPlayer());
		QString playerText("Not Owned");
		if (owner != NULL) {
			playerText = owner->getName().c_str();
		}

		QString armiesText(std::to_string(country.getArmies()).c_str());
		QGraphicsTextItem* armies = scene->addText(armiesText, font);
		// http://stackoverflow.com/a/946734
		int grey = playerColor.red()*0.299 + playerColor.green()*0.587 + playerColor.blue()*0.114;
		armies->setDefaultTextColor(QColor(grey < 186 ? Qt::white : Qt::black));
		armies->setPos(country.getPositionX()-8, country.getPositionY()-8);
		armies->setZValue(3);
	}

	std::map<const std::string, bool> visited = std::map<const std::string, bool>();
	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;
		visited.insert(std::pair<const std::string, bool>(country.getName(), false));
	}

	if (observedMap->getCountries().size() == 0) {
		return;
	}
	const Country* country = &observedMap->getCountries().begin()->second;
	connectNeighboursVisit(visited, country);
}

void MainWindow::connectNeighboursVisit(std::map<const std::string, bool>& visited, const Country* country) {
	QPen pen(QColor(0xFF, 0, 0, 0x40));
	pen.setWidth(1);

	bool& was_visited = visited.at(country->getName());
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour_str : observedMap->getNeighbours(country->getName())) {
		Country* neighbour = observedMap->getCountry(neighbour_str);
		QGraphicsLineItem* line = scene->addLine(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), pen);
		line->setZValue(1);
		connectNeighboursVisit(visited, neighbour);
	}
}

//void ClickableMap::mousePressEvent(QGraphicsSceneMouseEvent* w){
//}
