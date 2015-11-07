#include "playernamedialog.h"
#include "ui_playernamedialog.h"
#include <QDebug>

PlayerNameDialog::PlayerNameDialog(QWidget *parent) :QDialog(parent),ui(new Ui::PlayerNameDialog)
{
    ui->setupUi(this);
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
    this->parent()->findChild<QLabel*>("Player1")->setText(ui->lineEdit->text());
}
