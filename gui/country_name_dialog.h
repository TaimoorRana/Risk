#ifndef COUNTRYNAMEDIALOG_H
#define COUNTRYNAMEDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class CountryNameDialog;
}

class CountryNameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CountryNameDialog(QWidget *parent = 0);
    ~CountryNameDialog();
    QString getText();
    QString getContinentName();
    void setLastContinentName(const QString& lastContinent);
    QString getCountryName();

private:
    Ui::CountryNameDialog *ui;
};

#endif // COUNTRYNAMEDIALOG_H
