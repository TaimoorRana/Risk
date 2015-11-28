#include "fortify_dialog.h"
#include "game_driver.h"
#include "ui_fortify_dialog.h"

/**
 * @brief Pop-up dialog to configure a fortification move
 */
FortifyDialog::FortifyDialog(GameDriver* driver, Country* originCountry, Country* destinationCountry, QWidget *parent) :QDialog(parent), ui(new Ui::FortifyDialog)
{
	ui->setupUi(this);
	ui->armiesSlider->setMaximum(originCountry->getArmies() - 1);
	ui->armiesSlider->setMinimum(0);
	this->driver = driver;
	this->setOriginCountry(originCountry);
	this->setDestinationCountry(destinationCountry);
}

FortifyDialog::~FortifyDialog()
{
	delete ui;
}

/**
 * @brief Sets the name of the origin country from which the player will be moving armies
 * @param countryName The name of the country of origin
 */
void FortifyDialog::setOriginCountry(Country* country)
{
	this->originCountry = country;
	ui->originCountry->setText(QString::fromStdString(country->getName()));
}

/**
 * @brief FortifyDialog::setDestinationCountryName This method sets the name of the destination country to which the player will be moving armies
 * @param countryName The name of the destination country
 */
void FortifyDialog::setDestinationCountry(Country* country)
{
	this->destinationCountry = country;
	ui->destinationCountry->setText(QString::fromStdString(country->getName()));
}

/**
 * @brief Slot implementation start the fortification action.
 */
void FortifyDialog::accept()
{
	int armies = ui->armiesSlider->value();
	this->driver->fortifyCountry(this->originCountry, this->destinationCountry, armies);
	this->close();
	// TODO: error validation
}
