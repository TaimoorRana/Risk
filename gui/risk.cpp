#include "risk.h"
#include "ui_risk.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
	ui(new Ui::MainWindow) {
		ui->setupUi(this);
	}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pushButton_clicked() {
}
