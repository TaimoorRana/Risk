#include "country_name_dialog.h"
#include "ui_country_name_dialog.h"
#include <QDebug>
#include <QString>

CountryNameDialog::CountryNameDialog(QWidget *parent) :QDialog(parent),ui(new Ui::CountryNameDialog)
{
    ui->setupUi(this);
}

CountryNameDialog::~CountryNameDialog()
{
    delete ui;
}

QString CountryNameDialog::getCountryName()
{
    return ui->CountryNameLineEdit->text();
}

void CountryNameDialog::setLastContinentName(const QString& lastContinent){
    ui->ContinentNameLineEdit->setText(lastContinent);
}

QString CountryNameDialog::getContinentName()
{
    return ui->ContinentNameLineEdit->text();
}
