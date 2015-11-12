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
    explicit FortifyDialog( Country* aCountry, QWidget *parent = 0);
    ~FortifyDialog();
    void setOriginCountryName(QString name);
    void setDestinationCountryName(QString name);
    QString getFortificationNumber();
    void accept();
private:
    Ui::FortifyDialog *ui;
};

#endif // FORTIFY_DIALOG_H
