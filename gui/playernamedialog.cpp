#include <QDir>
#include <QFileDialog>

#include "mainscreen.h"
#include "playernamedialog.h"
#include "ui_playernamedialog.h"

PlayerNameDialog::PlayerNameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlayerNameDialog)
{
	ui->setupUi(this);
	setComboBox();
}

PlayerNameDialog::~PlayerNameDialog() {
	delete ui;
}

void PlayerNameDialog::setComboBox(){
	for (int x = 0 ; x < totalCPU; x++){
		ui->AIPlayerCountComboBox->addItem(QString::number(x+1));
	}
}

std::string PlayerNameDialog::getPlayerName() {
	return ui->playerNameLineEdit->text().toStdString();
}

std::string PlayerNameDialog::getMapPath() {
	return ui->mapPathLineEdit->text().toStdString();
}

int PlayerNameDialog::getAIPlayerCount() {
	return ui->AIPlayerCountComboBox->currentText().toInt();
}

void PlayerNameDialog::on_mapPathBrowsePushButton_clicked() {
	QString filename(QFileDialog::getOpenFileName(this, tr("Open map"), QDir::currentPath(), tr("Risk map files (*.map)")));
	ui->mapPathLineEdit->setText(filename);
}
