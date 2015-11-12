#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent, Player *subject, MapScene* scene) : QWidget(parent),ui(new Ui::PlayerInfoWidget)
{
	ui->setupUi(this);
	this->player = subject;
	this->scene = scene;
	player->registerObserver(this);
	update();
}

PlayerInfoWidget::~PlayerInfoWidget()
{
	delete ui;
	player = nullptr;
}

void PlayerInfoWidget::update()
{
	QColor playerColor = this->scene->getPlayerColor(this->player->getName());
	ui->colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + playerColor.name().toStdString() + "; }"));
	ui->nameValueLabel->setText(QString::fromStdString(player->getName()));
	ui->countriesValueLabel->setText(QString::number(player->getCountriesOwned().size()));
	ui->continentsValueLabel->setText(QString::number(player->getContinentsOwned().size()));
	ui->armiesValueLabel->setText(QString::number(player->getTotalArmy()));
	ui->reinforcementValue->setText(QString::number(player->getReinforcements()));
	this->repaint();
}

