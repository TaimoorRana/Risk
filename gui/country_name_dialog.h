#ifndef COUNTRYNAMEDIALOG_H
#define COUNTRYNAMEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CountryNameDialog;
}

/**
 * @brief The CountryNameDialog class serves as a lightweight class with a ui to
 *  capture Country name and Continent name when entering Country objects within
 * the MapEditor.
 */
class CountryNameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CountryNameDialog(QWidget *parent = 0);
    ~CountryNameDialog();
    QString getText();
    QString getContinentName();
    QString getCountryName();
	void setExistingCountryName(const QString& existingCountry);
    void setLastContinentName(const QString& lastContinent);
	void disableContinentEntry();
private:
    Ui::CountryNameDialog *ui;
};

#endif // COUNTRYNAMEDIALOG_H
