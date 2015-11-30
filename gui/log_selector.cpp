#include <QString>
#include "log_selector.h"
#include "ui_log_selector.h"

LogSelector::LogSelector(std::vector<std::string> playerNames, QWidget *parent): QDialog(parent), ui(new Ui::LogSelector) {
	ui->setupUi(this);
	for (auto &playerName : playerNames) {
		ui->PlayersCombo->insertItem(playerNames.size(), QString::fromStdString(playerName));
	}
}

LogSelector::~LogSelector(){
	delete ui;
}

std::string LogSelector::getSelectedPlayer() {
	return ui->PlayersCombo->currentText().toStdString();
}

std::string LogSelector::getSelectedPhase() {
	return ui->PhasesCombo->currentText().toStdString();
}
