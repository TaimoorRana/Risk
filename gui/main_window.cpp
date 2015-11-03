#include <QDir>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>

#include "debug.h"
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(Map* map, QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	observedMap = map;

	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

  QPen pen(Qt::black);
  pen.setWidth(2);

  scene->addRect(50, 0, 100, 50, pen, QBrush(Qt::blue));
  scene->addEllipse(0, -100, 100, 300, pen, QBrush(Qt::green));
  scene->addText("Example Text", QFont("Verdana", 20));
}


MainWindow::~MainWindow() {
	delete ui;
	scene->clear();
	delete scene;
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

void MainWindow::observedUpdated() {
	scene->clear();

	QFileInfo mapFile(ui->filenameLineEdit->text());
	QFileInfo bmpFile(mapFile.path() + "/" + mapFile.baseName() + ".bmp");
	QPixmap bg(bmpFile.absoluteFilePath());
	scene->addPixmap(bg);

	int diameter = 20;
	QPen pen(Qt::black);
  pen.setWidth(1);

	for (auto const &ent1 : observedMap->countries) {
		Country* country = ent1.second;
		scene->addEllipse(country->getPositionX()-diameter/2, country->getPositionY()-diameter/2, diameter, diameter, pen, QBrush(Qt::green));
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
	QPen pen(Qt::red);
  pen.setWidth(1);

	bool& was_visited = visited.at(country);
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbour : country->getNeighbours()) {
		scene->addLine(country->getPositionX(), country->getPositionY(), neighbour->getPositionX(), neighbour->getPositionY(), pen);
		connectNeighboursVisit(visited, neighbour);
	}
}
