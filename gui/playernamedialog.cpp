#include "playernamedialog.h"
#include "ui_playernamedialog.h"
#include <QDebug>

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

QString PlayerNameDialog::getText()
{
    return ui->lineEdit->text();
}


void PlayerNameDialog::on_buttonBox_accepted()
{
    QString name = "Name : " + ui->lineEdit->text();
    this->parent()->findChild<QLabel*>("nameLabel")->setText(name);
}


