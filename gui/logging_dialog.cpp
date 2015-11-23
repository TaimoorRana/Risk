#include "logging_dialog.h"
#include "ui_logging_dialog.h"

#include <QCheckBox>


LoggingDialog::LoggingDialog(const std::map<std::string, Player> &players, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoggingDialog)
{
	ui->setupUi(this);
}

LoggingDialog::~LoggingDialog()
{
	delete ui;
}

void LoggingDialog::addObservableItemPlayer(QString label){
	QCheckBox *checkbox = new QCheckBox(label, this);
	ui->playerLoggerLayout->addWidget(checkbox);
}

void LoggingDialog::addObservableItemPhase(QString label){
	QCheckBox *checkbox = new QCheckBox(label, this);
	ui->phaseLoggerLayout->addWidget(checkbox);
}

void LoggingDialog::populatePlayers(){
	
}
