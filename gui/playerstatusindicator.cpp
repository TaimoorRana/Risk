#include "playerstatusindicator.h"
#include "ui_playerstatusindicator.h"

PlayerStatusIndicator::PlayerStatusIndicator(std::string baseColor, QWidget *parent) :QWidget(parent),ui(new Ui::PlayerStatusIndicator)
{
	ui->setupUi(this);
	this->baseColor = baseColor;
	this->setStyleSheet(QString::fromStdString("background-color : " + baseColor + ";"));
	this->setPalette(QPalette(qRgb(128,128,0)));
	//this->setStyleSheet(QString::fromStdString("#indicator{background-color : " + this->indicatorColor + ";}"));
}

PlayerStatusIndicator::~PlayerStatusIndicator()
{
	delete ui;
}

void PlayerStatusIndicator::turnOn()
{
	//this->setStyleSheet(QString::fromStdString("QWidget#indicator{background-color : " + this->indicatorColor + ";}"));
}

void PlayerStatusIndicator::turnOff()
{
	//this->setStyleSheet(QString::fromStdString("QWidget{background-color : " + baseColor + ";}"));
}
