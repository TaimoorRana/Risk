#include "log_selector.h"
#include "ui_log_selector.h"
#include <string>
#include <QString>

LogSelector::LogSelector(QWidget *parent, int numberOfPlayers): QDialog(parent), ui(new Ui::LogSelector){
	ui->setupUi(this);
	generatePlayers(numberOfPlayers);

}

LogSelector::~LogSelector(){
	delete ui;
}

int LogSelector::getSelectedPlayer()
{
	return ui->PlayersCombo->currentText().toInt();
}

std::string LogSelector::getSelectedPhase()
{
	return ui->PhasesCombo->currentText().toStdString();
}

void LogSelector::generatePlayers(int numberOfPlayers)
{
	//ui->PlayersCombo->addItem("boker");

	for(int i=0;i<numberOfPlayers;i++){


		ui->PlayersCombo->addItem(QString("%1").arg(i+1));
	}

}




