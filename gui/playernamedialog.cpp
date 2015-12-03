#include <QDir>
#include <QFileDialog>

#include "mainscreen.h"
#include "playernamedialog.h"
#include "ui_playernamedialog.h"

PlayerNameDialog::PlayerNameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlayerNameDialog) {
    ui->setupUi(this);
}

PlayerNameDialog::~PlayerNameDialog() {
  delete ui;
}

std::string PlayerNameDialog::getMapPath() {
	return ui->mapPathLineEdit->text().toStdString();
}

int PlayerNameDialog::getPlayerCount() {
	return ui->AIPlayerCountComboBox->currentText().toInt();
}

void PlayerNameDialog::on_mapPathBrowsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk map files (*.map *.xml)")));
	this->raise();
	if (filename.length() > 0) {
		ui->mapPathLineEdit->setText(filename);
	}
}
