#include <QDir>
#include <QColor>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QGraphicsLineItem>
#include <QPen>

#include "debug.h"
#include "map_editor.h"
#include "map_renderer.h"
#include "qgraphics_country_item.h"
#include "qgraphics_country_edge_item.h"

MapEditor::MapEditor(QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MapEditor;
	ui->setupUi(this);

	observedMap = new RiskMap();
	observedMap->attachObserver(this);

	scene = new MapScene(observedMap, this);
	scene->setEditable(true);
	ui->graphicsView->setScene(scene);

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
	}
	else {
		ui->loadPushButton->setEnabled(false);
		ui->clearMapPushButton->setEnabled(false);
	}
}

void MapEditor::on_browsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk Map Files (*.xml *.map)")));
	this->raise();
	ui->filenameLineEdit->setText(filename);
}

bool MapEditor::hasEnding (std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}

bool MapEditor::loadXML(std::string path, RiskMap* map) {
	map->setNotificationsEnabled(false);

	std::ifstream infile(path);
	cereal::XMLInputArchive input(infile);
//	input(cereal::make_nvp("driver", *driver));
	input(cereal::make_nvp("maprisk", *map));

	map->setNotificationsEnabled(true);
//	map->notifyObservers();
	return true;
}


void MapEditor::on_loadPushButton_clicked() {
	ui->clearMapPushButton->setEnabled(true);
	this->mapPath = ui->filenameLineEdit->text().toStdString();
	if(MapEditor::hasEnding(this->mapPath,"map")){
		debug("Loading MAP file");
		observedMap->parse(this->mapPath);
	}
	else{
		debug("Loading XML file");
		/* parsing XML file*/
		loadXML(mapPath, observedMap);
	}


	if(!observedMap->validate()){
		QMessageBox errorDialog(this);
		errorDialog.setWindowTitle("Error!");
		errorDialog.setText("Invalid map");
		errorDialog.setDetailedText("The map did not validate. Please ensure that the set of all of countries are a connected graph, and countries in each continent are also connected subgraphs.");
		errorDialog.exec();
		observedMap->clear();
	}
	this->observedMap->notifyObservers();
}

void MapEditor::on_clearMapPushButton_clicked() {
	observedMap->clear();
	debug("Loading new map");
	ui->clearMapPushButton->setEnabled(false);
	ui->saveMapPushButton->setEnabled(false);
}


void MapEditor::on_saveMapPushButton_clicked(){
	debug("Save Button clicked\n");

	//Removes fatal bug.
	if(this->observedMap->isEmpty()){
		debug("Can't save an empty map.");
		this->ui->saveMapPushButton->setDisabled(true);
		return;
	}

	if(QString::compare((ui->saveComboBox->currentText()), QString::fromStdString(".map"), Qt::CaseInsensitive) == 0)
	{
		this->saveMode = MAP;
		debug("MAP File format selected.");
	}
	else
	{
		this->saveMode = XML;
		debug("XML File format selected.");
	}

	if(true){//observedMap->validate()){
		observedMap->save(saveMode);
	}
	else{
		QMessageBox errorDialog(this);
		errorDialog.setWindowTitle("Error!");
		errorDialog.setText("Invalid map");
		errorDialog.setDetailedText("The map did not validate. Please ensure that the set of all of countries are a connected graph, and countries in each continent are also connected subgraphs.");
		errorDialog.exec();
		return;
	}
}

void MapEditor::resetToolbar() {
	ui->addCountryPushButton->setChecked(false);
	ui->removeCountryPushButton->setChecked(false);
	ui->addNeighbourPushButton->setChecked(false);
	ui->removeNeighbourPushButton->setChecked(false);
	if(this->observedMap->isEmpty()){
		this->ui->saveMapPushButton->setDisabled(true);
		this->ui->clearMapPushButton->setDisabled(true);
	}
	else{
		this->ui->saveMapPushButton->setEnabled(true);
		this->ui->clearMapPushButton->setEnabled(true);
	}
}

void MapEditor::on_addCountryPushButton_clicked(){
	bool checked = ui->addCountryPushButton->isChecked();
	this->resetToolbar();
	ui->addCountryPushButton->setChecked(checked);
	this->tool = checked ? ADDCOUNTRY : OFF;
}

void MapEditor::on_removeCountryPushButton_clicked(){
	bool checked = ui->removeCountryPushButton->isChecked();
	this->resetToolbar();
	ui->removeCountryPushButton->setChecked(checked);
	this->tool = checked ? REMCOUNTRY : OFF;
}

void MapEditor::on_addNeighbourPushButton_clicked(){
	bool checked = ui->addNeighbourPushButton->isChecked();
	this->resetToolbar();
	ui->addNeighbourPushButton->setChecked(checked);
	this->tool = checked ? ADDLINK : OFF;
}

void MapEditor::on_removeNeighbourPushButton_clicked(){
	bool checked = ui->removeNeighbourPushButton->isChecked();
	this->resetToolbar();
	ui->removeNeighbourPushButton->setChecked(checked);
	this->tool = checked ? REMLINK : OFF;
}

void MapEditor::observedUpdated() {
	MapRenderer::updateScene(this->observedMap, this->scene, this->mapPath, true);
}
