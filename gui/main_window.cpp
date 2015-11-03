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

#include "debug.h"
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(Map* map, QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	observedMap = map;

	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);
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

void MainWindow::on_randOwnerPushButton_clicked() {
	mt19937::result_type seed = time(0);
	auto player_rand = std::bind(std::uniform_int_distribution<int>(0, observedMap->players.size()-1), mt19937(seed));

	for (auto const &ent1 : observedMap->countries) {
		Country* country = ent1.second;

		auto it = observedMap->players.begin();
		std::advance(it, player_rand());
		Player* player = it->second;
		country->setOwner(player);
	}
}

void MainWindow::on_randArmiesPushButton_clicked() {
	for (auto const &ent1 : observedMap->countries) {
		Country* country = ent1.second;
		country->setSoldiers(rand() % 10);
	}
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

	mt19937::result_type seed = 4;
	auto color_rand = std::bind(std::uniform_int_distribution<int>(0, 255), mt19937(seed));

	std::map<const Continent*, QColor> continentPalette = std::map<const Continent*, QColor>();
	for (auto const &ent1 : observedMap->continents) {
		Continent* continent = ent1.second;
		continentPalette.insert(std::pair<const Continent*, QColor>(continent, QColor(color_rand(), color_rand(), color_rand())));
	}

	std::map<const Player*, QColor> playerPalette = std::map<const Player*, QColor>();
	for (auto const &ent1 : observedMap->players) {
		Player* player = ent1.second;
		playerPalette.insert(std::pair<const Player*, QColor>(player, QColor(color_rand(), color_rand(), color_rand())));
	}
	playerPalette.insert(std::pair<const Player*, QColor>(NULL, QColor(204, 204, 204)));

	for (auto const &ent1 : observedMap->countries) {
		Country* country = ent1.second;

		diameter = 30;
		QColor continentColor(continentPalette.at(country->getContinent()));
		QGraphicsEllipseItem* ellipse = scene->addEllipse(country->getPositionX()-diameter/2, country->getPositionY() - diameter/2, diameter, diameter, QPen(), QBrush(continentColor));
		ellipse->setZValue(1);

		diameter = 15;
		QColor playerColor(playerPalette.at(country->getOwner()));
		ellipse = scene->addEllipse(country->getPositionX()-diameter/2, country->getPositionY() - diameter/2, diameter, diameter, QPen(), QBrush(playerColor));
		ellipse->setZValue(2);

		Player* owner = country->getOwner();
		QString playerText("Not Owned");
		if (owner != NULL) {
			playerText = owner->getName().c_str();
		}

		QString armiesText(std::to_string(country->getSoldiers()).c_str());
		QGraphicsTextItem* armies = scene->addText(armiesText, font);
		// http://stackoverflow.com/a/946734
		int grey = playerColor.red()*0.299 + playerColor.green()*0.587 + playerColor.blue()*0.114;
		armies->setDefaultTextColor(QColor(grey < 186 ? Qt::white : Qt::black));
		armies->setPos(country->getPositionX()-8, country->getPositionY()-8);
		armies->setZValue(3);
	}

	std::map<const Country*, bool> visited = std::map<const Country*, bool>();
	for (auto const &ent1 : observedMap->countries) {
		Country* country = ent1.second;
		visited.insert(std::pair<const Country*, bool>(country, false));
	}

	Country* country = NULL;
	country = observedMap->countries.begin()->second;
	connectNeighboursVisit(visited, country);
}

void MainWindow::connectNeighboursVisit(std::map<const Country*, bool>& visited, Country* country) {
	QPen pen(QColor(0xFF, 0, 0, 0x40));
  pen.setWidth(1);

	bool& was_visited = visited.at(country);
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour : country->getNeighbours()) {
		QGraphicsLineItem* line = scene->addLine(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), pen);
		line->setZValue(1);
		connectNeighboursVisit(visited, neighbour);
	}
}
