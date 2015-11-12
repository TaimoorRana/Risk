#include "fortify_dialog.h"
#include "ui_fortify_dialog.h"

FortifyDialog::FortifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FortifyDialog)
{
    ui->setupUi(this);
}

FortifyDialog::~FortifyDialog()
{
    delete ui;
}

void FortifyDialog::setOriginCountryName(QString countryName)
{
    ui->destinationCountry->setText(countryName);
}

void FortifyDialog::setDestinationCountryName(QString countryName)
{
    ui->originCountry->setText(countryName);
}

QString FortifyDialog::getFortificationNumber()
{
    return ui->numArmies->text();
}
