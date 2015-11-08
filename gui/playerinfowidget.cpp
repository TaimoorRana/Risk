#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent, PlayerView *pv) :QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->pv =pv;
	setPlayerInfo();
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;
}

void PlayerInfoWidget::setPlayerInfo()
{
	ui->nameValueLabel->setText(QString::fromStdString(pv->getName()));
	ui->countriesValueLabel->setText(QString::number(pv->getCountriesOwned().size()));
	ui->continentsValueLabel->setText(QString::number(pv->getContinentsOwned().size()));
	ui->armiesValueLabel->setText(QString::number(pv->getNumberOfArmies()));
}

