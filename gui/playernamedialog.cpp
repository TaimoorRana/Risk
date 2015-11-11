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
	dynamic_cast<MainScreen*>(this->parent())->setPLayerName(ui->lineEdit->text());
	dynamic_cast<MainScreen*>(this->parent())->setCPUs(ui->comboBox->currentText().toInt());
	dynamic_cast<MainScreen*>(this->parent())->setupPlayers();
	dynamic_cast<MainScreen*>(this->parent())->show();

}


