#include <QDir>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QInputDialog>

#include <random>
#include <functional>
#include <time.h>

#include "debug.h"
#include "main_window.h"
#include "ui_main_window.h"
#include <QMouseEvent>
#include <qdebug.h>

#include "country_qgraphics_object.h"
#include "custom_country_connection.h"

MainWindow::MainWindow(RiskMap* map, QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MainWindow;
	ui->setupUi(this);
    observedMap = map;
	scene = new MapScene(map, this);
	ui->graphicsView->setScene(scene);
    setMouseTracking(true);
    tool = OFF;
}

MainWindow::~MainWindow() {
	scene->clear();
	delete scene;
	delete ui;
}

ToolMode MainWindow::getSelectedTool(){
	return tool;
}


bool MainWindow::validateFilename(const QString& text) {
	QFileInfo mapFile(text);
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	return mapFile.exists() && bmpFile.exists();
}

void MainWindow::on_filenameLineEdit_textChanged(QString text) {
	if (this->validateFilename(text)) {
		ui->loadPushButton->setEnabled(true);
		ui->newPushButton->setEnabled(true);
	}
	else {
		ui->loadPushButton->setEnabled(false);
		ui->newPushButton->setEnabled(false);
	}
}

void MainWindow::on_browsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk map files (*.map)")));
	ui->filenameLineEdit->setText(filename);
}

void MainWindow::on_loadPushButton_clicked() {
	observedMap->parse(ui->filenameLineEdit->text().toStdString());
	if(!observedMap->validate()){
		debug("Failed to load Map.");
		observedMap->clear();
	}

}

void MainWindow::on_newPushButton_clicked() {
	observedMap->clear();
	qDebug("Loading new map");
}



void MainWindow::on_saveMapPushButton_clicked(){
    debug("Save Button clicked\n");
	if(observedMap->validate()){
		observedMap->save("riskmap_test0.map");
	}
	else{
		debug("Map not valid, not saving...");
		return;
	}
}

void MainWindow::on_addCountryPushButton_clicked(){
	debug("Add Country");
    tool = ADDCOUNTRY;
}

void MainWindow::on_removeCountryPushButton_clicked(){
    debug("Remove Country");
    tool = REMCOUNTRY;
}

void MainWindow::on_moveCountryPushButton_clicked(){
    debug("Move Country");
    tool = MOVCOUNTRY;
}


void MainWindow::on_addNeighbourPushButton_clicked(){
    debug("Add Neighbour");
    tool = ADDLINK;
}

void MainWindow::on_removeNeighbourPushButton_clicked(){
    debug("Remove Neighbour");
    tool = REMLINK;
}



void MainWindow::   observedUpdated() {
//    QMutexLocker locker(&mutex);
	scene->clear();

	debug("render event");

	QFileInfo mapFile(ui->filenameLineEdit->text());
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	scene->addPixmap(bg);

	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;
		CountryQGraphicsObject* item = new CountryQGraphicsObject(observedMap->getCountry(country.getName()));
		item->setPos(country.getPositionX(), country.getPositionY());
		this->scene->addItem(item);
		item->setZValue(10);
	}

	std::map<const std::string, bool> visited = std::map<const std::string, bool>();
	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;
		visited.insert(std::pair<const std::string, bool>(country.getName(), false));
	}

	if (observedMap->getCountries().size() == 0) {
		return;
	}
//	const Country* country = &observedMap->getCountries().begin()->second;

	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;
		connectNeighboursVisit(visited, &country);
	}
}

void MainWindow::connectNeighboursVisit(std::map<const std::string, bool>& visited, const Country* country) {


	bool& was_visited = visited.at(country->getName());
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour_str : observedMap->getNeighbours(country->getName())) {
		Country* neighbour = observedMap->getCountry(neighbour_str);
//        CustomCountryConnection* line = scene->addLine(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), pen);
//        CustomCountryConnection line(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), dynamic_cast<QGraphicsItem*>(scene));
//        scene->addItem(dynamic_cast<QGraphicsItem*>(&line));
        CustomCountryConnection *line = new CustomCountryConnection(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), dynamic_cast<QGraphicsItem*>(scene));
        this->scene->addItem(line);

        line->setBoundingRegionGranularity(1.0);
        line->setZValue(1);
		connectNeighboursVisit(visited, neighbour);
	}
}

