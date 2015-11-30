#ifndef FORTIFY_DIALOG_H
#define FORTIFY_DIALOG_H

#include <QDialog>
#include <QString>
#include "country.h"
#include "game_driver.h"
#include "mainscreen.h"

namespace Ui {
class FortifyDialog;
}

class FortifyDialog : public QDialog
{
	Q_OBJECT

public:
	explicit FortifyDialog(GameDriver* driver, Country* originCountry, Country* destinationCountry, QWidget *parent = 0);
	~FortifyDialog();
	void setOriginCountry(Country* country);
	void setDestinationCountry(Country* country);
	void accept();
private:
	Ui::FortifyDialog *ui;
	GameDriver* driver = nullptr;
	Country* originCountry = nullptr;
	Country* destinationCountry = nullptr;
};

#endif // FORTIFY_DIALOG_H
