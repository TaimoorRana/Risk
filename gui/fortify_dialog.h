#ifndef FORTIFY_DIALOG_H
#define FORTIFY_DIALOG_H

#include <QDialog>
#include <QString>
#include "country.h"

namespace Ui {
class FortifyDialog;
}

class FortifyDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief FortifyDialog::FortifyDialog
     * @param firstCountry A pointer to the origin country
     * @param secondCountry A pointer to the destination country
     * @param parent The parent window that contains the dialog
     */
    explicit FortifyDialog( Country* firstCountry, Country* secondCountry, QWidget *parent = 0);

    /**
     * @brief FortifyDialog::~FortifyDialog
     */
    ~FortifyDialog();

    /**
     * @brief FortifyDialog::setOriginCountryName This method sets the name of the origin country from which the player will be moving armies
     * @param countryName The name of the country of origin
     */
    void setOriginCountryName(QString countryName);

    /**
     * @brief FortifyDialog::setDestinationCountryName This method sets the name of the destination country to which the player will be moving armies
     * @param countryName The name of the destination country
     */
    void setDestinationCountryName(QString countryName);

    /**
     * @brief FortifyDialog::getFortificationNumber This method gets the number of armies to be moved from the slider
     * @return The number of armies selected by the user through the slider
     */
    QString getFortificationNumber();

    /**
     * @brief FortifyDialog::accept This method updates the countries with the selected fortification upon pressing "OK"
     */
    void accept();
private:
    Ui::FortifyDialog *ui; ///< The dialog box object to access all the UI elements
    Country* firstCountry; ///< The country of origin from which armies will be moved
    Country* secondCountry; ///< The destination country to which armies will be moved
};

#endif // FORTIFY_DIALOG_H
