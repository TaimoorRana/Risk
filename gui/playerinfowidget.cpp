#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent, Player *subject, MapScene* scene) : QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->player = subject;
	this->scene = scene;
	this->player->attachObserver(this);
	QColor playerColor = this->scene->getPlayerColor(this->player->getName());
	std::string hexColor = playerColor.name().toStdString();
	playerStatusIndicator = new PlayerStatusIndicator(hexColor,this);
	playerStatusIndicator->turnOn();
	ui->horizontalLayout_4->addWidget(playerStatusIndicator);
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;
	this->player->detachObserver(this);
	delete this->playerStatusIndicator;
}

void PlayerInfoWidget::observedUpdated()
{
	//ui->colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	//ui->widget->setStyleSheet(QString::fromStdString("background-color : " + hexColor + ";"));
	ui->nameValueLabel->setText(QString::fromStdString(this->player->getName()));
	ui->countriesValueLabel->setText(QString::number(this->player->getCountriesOwned().size()));
	ui->continentsValueLabel->setText(QString::number(this->player->getContinentsOwned().size()));
	ui->armiesValueLabel->setText(QString::number(this->player->getTotalArmy()));
	ui->reinforcementValue->setText(QString::number(this->player->getReinforcements()));
	this->repaint();
}

