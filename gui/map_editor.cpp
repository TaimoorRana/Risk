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
	this->mapPath = ui->filenameLineEdit->text().toStdString();
	observedMap->parse(this->mapPath);
	if(!observedMap->validate()){
		debug("Failed to load Map.");
		observedMap->clear();
	}
}

void MapEditor::on_newPushButton_clicked() {
	observedMap->clear();
	debug("Loading new map");
}

void MapEditor::on_saveMapPushButton_clicked(){
		debug("Save Button clicked\n");
	if(observedMap->validate()){
		observedMap->save("riskmap_test0.map");
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
