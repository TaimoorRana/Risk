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
#include "map_editor.h"
#include "ui_map_editor.h"
#include <QMouseEvent>
#include <qdebug.h>

#include "qgraphics_country_item.h"


MapEditor::MapEditor(QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MapEditor;
	ui->setupUi(this);

	observedMap = new RiskMap();
	observedMap->attachObserver(this);

	scene = new MapScene(observedMap, this);
	ui->graphicsView->setScene(scene);

	setMouseTracking(true);
	tool = OFF;
}

MapEditor::~MapEditor() {
	scene->clear();
	delete observedMap;
	delete scene;
	delete ui;
}

ToolMode MapEditor::getSelectedTool(){
	return tool;
}


bool MapEditor::validateFilename(const QString& text) {
	QFileInfo mapFile(text);
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	return mapFile.exists() && bmpFile.exists();
}

void MapEditor::on_filenameLineEdit_textChanged(QString text) {
	if (this->validateFilename(text)) {
		ui->loadPushButton->setEnabled(true);
		ui->newPushButton->setEnabled(true);
	}
	else {
		ui->loadPushButton->setEnabled(false);
		ui->newPushButton->setEnabled(false);
	}
}

void MapEditor::on_browsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk map files (*.map)")));
	ui->filenameLineEdit->setText(filename);
}

void MapEditor::on_loadPushButton_clicked() {
	observedMap->parse(ui->filenameLineEdit->text().toStdString());
	if(!observedMap->validate()){
		debug("Failed to load Map.");
		observedMap->clear();
	}

}

void MapEditor::on_newPushButton_clicked() {
	observedMap->clear();
	qDebug("Loading new map");
}



void MapEditor::on_saveMapPushButton_clicked(){
		debug("Save Button clicked\n");
	if(observedMap->validate()){
		observedMap->save("riskmap_test0.map");
	}
	else{
		debug("Map not valid, not saving...");
		return;
	}
}

void MapEditor::on_addCountryPushButton_clicked(){
	debug("Add Country");
		tool = ADDCOUNTRY;
}

void MapEditor::on_removeCountryPushButton_clicked(){
		debug("Remove Country");
		tool = REMCOUNTRY;
}

void MapEditor::on_moveCountryPushButton_clicked(){
		debug("Move Country");
		tool = MOVCOUNTRY;
}


void MapEditor::on_addNeighbourPushButton_clicked(){
		debug("Add Neighbour");
		tool = ADDLINK;
}

void MapEditor::on_removeNeighbourPushButton_clicked(){
		debug("Remove Neighbour");
		tool = REMLINK;
}

void MapEditor::   observedUpdated() {
//    QMutexLocker locker(&mutex);
	scene->clear();

	debug("render event");

	QFileInfo mapFile(ui->filenameLineEdit->text());
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	scene->addPixmap(bg);

	for (auto const &ent1 : observedMap->getCountries()) {
		const Country& country = ent1.second;
		QGraphicsCountryItem* item = new QGraphicsCountryItem(observedMap->getCountry(country.getName()));
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

void MapEditor::connectNeighboursVisit(std::map<const std::string, bool>& visited, const Country* country) {
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

