#include "country_name_dialog.h"
#include "ui_country_name_dialog.h"
#include <QDebug>

CountryNameDialog::CountryNameDialog(QWidget *parent) :QDialog(parent),ui(new Ui::CountryNameDialog)
{
    ui->setupUi(this);
}

CountryNameDialog::~CountryNameDialog()
{
    delete ui;
}

QString CountryNameDialog::getText()
{
    return ui->lineEdit->text();
}


void CountryNameDialog::on_buttonBox_accepted()
{
    this->parent()->findChild<QLabel*>("Player1")->setText(ui->lineEdit->text());
}
