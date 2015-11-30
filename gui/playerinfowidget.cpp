#include <QString>
#include "playerinfowidget.h"
#include "risk_map.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(GameDriver* driver, Player *subject, QColor playerColor, QWidget *parent) : QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->player = subject;
	this->playerColor = playerColor;
	this->driver = driver;

	this->player->attachObserver(this);
	this->driver->attachObserver(this);
	this->observedUpdated();
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;

	this->player->detachObserver(this);
	this->driver->detachObserver(this);
}

void PlayerInfoWidget::observedUpdated()
{
	RiskMap* map = this->driver->getRiskMap();
	std::string hexColor = this->playerColor.name().toStdString();
	ui->colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	if (this->driver->getCurrentPlayerName() == this->player->getName()) {
		ui->nameValueLabel->setText(QString::fromStdString("<b>" + this->player->getName() + "</b>"));
	}
	else {
		ui->nameValueLabel->setText(QString::fromStdString(this->player->getName()));
	}

	int totalArmy = 0;
	string_set countriesOwned = map->getCountriesOwnedByPlayer(this->player->getName());
	for (auto &countryName : countriesOwned) {
		Country* country = map->getCountry(countryName);
		totalArmy += country->getArmies();
	}

	ui->countriesValueLabel->setText(QString::number(countriesOwned.size()));
	ui->continentsValueLabel->setText(QString::number(map->getContinentsOwnedByPlayer(this->player->getName()).size()));
	ui->armiesValueLabel->setText(QString::number(totalArmy));
	ui->reinforcementValue->setText(QString::number(this->player->getReinforcements()));
	ui->battleWonLostValue->setText(QString("%1 / %2").arg(QString::number(this->player->getBattlesWon()), QString::number(this->player->getBattlesLost())));
	this->repaint();
}

