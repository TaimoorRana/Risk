#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>

#include "debug.h"
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

  QPen pen(Qt::black);
  pen.setWidth(2);

  QGraphicsRectItem* rectangle = scene->addRect(50, 0, 100, 50, pen, QBrush(Qt::blue));
  QGraphicsEllipseItem* ellipse = scene->addEllipse(0, -100, 100, 300, pen, QBrush(Qt::green));
  QGraphicsTextItem* text = scene->addText("Example Text", QFont("Verdana", 20));
}


MainWindow::~MainWindow() {
	delete ui;
    scene->clear();
	delete scene;
}

void MainWindow::on_pushButton_clicked() {
	debug("Pushbutton clicked");
}
