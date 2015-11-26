#include "logscreen.h"
#include "ui_logscreen.h"
#include <string>
#include <QString>
#include <QDebug>
#include "game_driver.h"
#include "game_modes.h"
using namespace std;
LogScreen::LogScreen(QWidget *parent): QMainWindow(parent),ui(new Ui::LogScreen)
{

	ui->setupUi(this);
	//update();

}

LogScreen::~LogScreen()
{
	GameDriver::getInstance()->detachObserver(this);
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

void LogScreen::setCurrentMode(Mode mode)
{
	currentMode = mode;
}

void LogScreen::update()
{	//ui->textEdit->setE
	ui->textEdit->insertPlainText("Hello Good day\n");
	ui->textEdit->insertPlainText("Boker");
	ui->textEdit->insertPlainText(QString::fromStdString(states));
	ui->textEdit->insertPlainText(QString("Players :%1").arg(players));
	qDebug("%d",players);
}

void LogScreen::observedUpdated()
{
	ui->textEdit->clear();
	string compareP = "Player "+ to_string(players);
	qDebug("%s",compareP);
	if(GameDriver::getInstance()->getCurrentPlayerName()== compareP || players==0){
		ui->textEdit->insertPlainText(QString::fromStdString(GameDriver::getInstance()->getCurrentPlayerName()));

	}
	//need to add states and clear screen
	//so that we have docorator for the three states.
	//playerLog.setName(), going to have to do garbage collection or end of round delete the player
	//and make a new one



}
