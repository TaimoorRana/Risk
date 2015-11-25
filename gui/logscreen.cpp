#include "logscreen.h"
#include "ui_logscreen.h"
#include <string>
#include <QString>
#include <QDebug>

LogScreen::LogScreen(QWidget *parent): QMainWindow(parent),ui(new Ui::LogScreen)
{

	ui->setupUi(this);
	update();

}

LogScreen::~LogScreen()
{
	delete ui;
}

void LogScreen::setPlayers(int nPlayers)
{
	players = nPlayers;
}

void LogScreen::setState(std::string stateSelected)
{
	states = stateSelected;
}

void LogScreen::update()
{	//ui->textEdit->setE
	ui->textEdit->insertPlainText("Hello Good day\n");
	ui->textEdit->insertPlainText("Boker");
	ui->textEdit->insertPlainText(QString::fromStdString(states));
	ui->textEdit->insertPlainText(QString("Players :%1").arg(players));
	qDebug("%d",players);
}



