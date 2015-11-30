#include <QString>
#include "log_selector.h"
#include "ui_log_selector.h"

LogSelector::LogSelector(QWidget *parent, int numberOfPlayers): QDialog(parent), ui(new Ui::LogSelector) {
	ui->setupUi(this);
	this->numberOfPlayers = numberOfPlayers;
	generatePlayers(numberOfPlayers);
}

LogSelector::~LogSelector(){
	delete ui;
}

int LogSelector::getSelectedPlayer() {
	qDebug("%d",ui->PlayersCombo->currentText().toInt());
	return ui->PlayersCombo->currentText().toInt();

}

std::string LogSelector::getSelectedPhase() {
	return ui->PhasesCombo->currentText().toStdString();
}

void LogSelector::setNumberPlayers(int players) {
	numberOfPlayers = players;
}

void LogSelector::generatePlayers(int numberOfPlayers) {
	for (int i=0;i<numberOfPlayers;i++) {
		ui->PlayersCombo->addItem(QString("%1").arg(i+1));
	}
}
