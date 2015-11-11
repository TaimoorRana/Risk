#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent, Player *subject) :QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->player =subject;
	update();
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;
	player = nullptr;
}

void PlayerInfoWidget::update()
{
	ui->nameValueLabel->setText(QString::fromStdString(player->getName()));
	ui->countriesValueLabel->setText(QString::number(player->getCountriesOwned().size()));
	ui->continentsValueLabel->setText(QString::number(player->getContinentsOwned().size()));
	ui->armiesValueLabel->setText(QString::number(player->getTotalArmy()));
	//this->update();
}

