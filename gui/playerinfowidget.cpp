#include <QString>

#include "game_driver.h"
#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent, Player *subject, MapScene* scene) : QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->player = subject;
	this->scene = scene;
	this->player->attachObserver(this);

	GameDriver* driver = GameDriver::getInstance();
	driver->attachObserver(this);

	this->observedUpdated();
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;

	this->player->detachObserver(this);

	GameDriver* driver = GameDriver::getInstance();
	driver->detachObserver(this);
}

void PlayerInfoWidget::observedUpdated()
{
	QColor playerColor = this->scene->getPlayerColor(this->player->getName());
	std::string hexColor = playerColor.name().toStdString();
	ui->colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	GameDriver* driver = GameDriver::getInstance();
	if (driver->getCurrentPlayerName() == this->player->getName()) {
		ui->nameValueLabel->setText(QString::fromStdString("<b>" + this->player->getName() + "</b>"));
	}
	else {
		ui->nameValueLabel->setText(QString::fromStdString(this->player->getName()));
	}
	ui->countriesValueLabel->setText(QString::number(this->player->getCountriesOwned().size()));
	ui->continentsValueLabel->setText(QString::number(this->player->getContinentsOwned().size()));
	ui->armiesValueLabel->setText(QString::number(this->player->getTotalArmy()));
	ui->reinforcementValue->setText(QString::number(this->player->getReinforcements()));
	this->repaint();
}

