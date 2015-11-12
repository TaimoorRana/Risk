#include "fortify_dialog.h"
#include "ui_fortify_dialog.h"
#include "debug.h"

FortifyDialog::FortifyDialog(Country* aCountry, QWidget *parent) :QDialog(parent), ui(new Ui::FortifyDialog)
{
    ui->setupUi(this);
    ui->armiesSlider->setMaximum(aCountry->getArmies()-1);
}

FortifyDialog::~FortifyDialog()
{
    delete ui;
}

void FortifyDialog::setOriginCountryName(QString countryName)
{
    ui->originCountry->setText(countryName);
}

void FortifyDialog::setDestinationCountryName(QString countryName)
{
    ui->destinationCountry->setText(countryName);
}

QString FortifyDialog::getFortificationNumber()
{
    return ui->numArmies->text();
}

void FortifyDialog::accept()
{
    // debug("Fortification accepted");
    this->close();
}
