#include <QString>

#include "playerinfowidget.h"
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
	std::string hexColor = this->playerColor.name().toStdString();
	ui->colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	if (this->driver->getCurrentPlayerName() == this->player->getName()) {
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

