#include "fortify_dialog.h"
#include "ui_fortify_dialog.h"
#include "debug.h"

FortifyDialog::FortifyDialog(Country* firstCountry, Country* secondCountry, QWidget *parent) :QDialog(parent), ui(new Ui::FortifyDialog)
{
    ui->setupUi(this);
    int currentArmiesInOriginCountry = firstCountry->getArmies();
    ui->armiesSlider->setMaximum(currentArmiesInOriginCountry-1);
    ui->armiesSlider->setMinimum(0);

    this->firstCountry = firstCountry;
    this->secondCountry = secondCountry;
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
    int armies = ui->armiesSlider->value();
    firstCountry->removeArmies(armies);
    secondCountry->addArmies(armies);
    
    this->close();
}
