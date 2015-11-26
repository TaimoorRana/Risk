#include "logscreen.h"
#include "ui_logscreen.h"
#include <string>
#include <QString>
#include <QDebug>
#include "game_driver.h"
#include "game_modes.h"
#include "component.h"
#include "decorator.h"
#include "player_log.h"
#include "concrete_attack.h"
#include "concrete_fortify.h"
#include "concrete_reinforce.h"
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
{
	ui->textEdit->insertPlainText("Hello Good day your logging has begun please select go to next phase to see logging effets\n");
	ui->textEdit->insertPlainText(QString("Players :%1").arg(players));
	qDebug("%d",players);
}

void LogScreen::observedUpdated()
{
	ui->textEdit->clear();
	string compareP = "Player "+ to_string(players);
	if(component ==nullptr){
		component = new PlayerLog(GameDriver::getInstance()->getCurrentPlayerName());

		//component-
	}
	else{

	}
	qDebug("%s",compareP);

	if(GameDriver::getInstance()->getCurrentPlayerName()== compareP || players==0){
		if(states=="All Phases"){

			if ( GameDriver::getInstance()->getCurrentMode()==REINFORCEMENTMODE){
				component = new ConcreteReinforce(component);
				ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));
			}
			else if (GameDriver::getInstance()->getCurrentMode()==ATTACKMODE){
				component = new ConcreteAttack(component);
				ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));
			}
			else if (GameDriver::getInstance()->getCurrentMode()==FORTIFICATIONMODE){
				component = new ConcreteFortify (component);
				ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));

			}

		}
		else if(states=="Fortify" && GameDriver::getInstance()->getCurrentMode()==FORTIFICATIONMODE){
			component = new ConcreteFortify(component);
			ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));
		}
		else if(states=="Attack" && GameDriver::getInstance()->getCurrentMode()==ATTACKMODE){
			component = new ConcreteAttack(component);
			ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));
		}
		else if(states=="Reinforce" && GameDriver::getInstance()->getCurrentMode()==REINFORCEMENTMODE){
			component = new ConcreteReinforce(component);
			ui->textEdit->insertPlainText(QString::fromStdString(component->getLog()));
		}
		//ui->textEdit->insertPlainText(QString::fromStdString(GameDriver::getInstance()->getCurrentPlayerName()));


	}
	//need to add states and clear screen
	//so that we have decorator for the three states.
	//playerLog.setName(), going to have to do garbage collection or end of round delete the player
	//and make a new one
	if(GameDriver::getInstance()->getCurrentMode()==FORTIFICATIONMODE){
		component = nullptr;
		delete component;
	}



}
