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
// this method does something cool!
QString CountryNameDialog::getCountryName()
{
    return ui->CountryNameLineEdit->text();
}

QString CountryNameDialog::getContinentName()
{
    return ui->ContinentNameLineEdit->text();
}

void CountryNameDialog::setLastContinentName(const QString& lastContinent){
    ui->ContinentNameLineEdit->setText(lastContinent);
}

void CountryNameDialog::setExistingCountryName(const QString& existingCountry){
	ui->CountryNameLineEdit->setText(existingCountry);
}

void CountryNameDialog::disableContinentEntry(){
	ui->ContinentNameLineEdit->setDisabled(true);
}
