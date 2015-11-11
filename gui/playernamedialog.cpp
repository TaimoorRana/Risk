#include "playernamedialog.h"
#include "ui_playernamedialog.h"
#include "mainscreen.h"
#include <QDebug>
#include <iostream>

PlayerNameDialog::PlayerNameDialog(QWidget *parent) :QDialog(parent),ui(new Ui::PlayerNameDialog)
{
	ui->setupUi(this);
	setComboBox();
}

void PlayerNameDialog::setComboBox(){
	for(int x = 0 ; x < totalCPU; x++){
		ui->comboBox->addItem(QString::number(x+1));
	}
}

PlayerNameDialog::~PlayerNameDialog()
{
	delete ui;
}

QString* PlayerNameDialog::getText()
{
	return name;
}

QString* PlayerNameDialog::getChoice()
{
	return choice;
}


void PlayerNameDialog::on_buttonBox_accepted()
{
	MainScreen* parent = dynamic_cast<MainScreen*>(this->parent());
	parent->setPlayerName(ui->lineEdit->text());
	parent->setCPUs(ui->comboBox->currentText().toInt());
	parent->setupPlayers();
	parent->show();
}


