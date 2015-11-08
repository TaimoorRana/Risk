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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CountryNameDialog *ui;
};

#endif // COUNTRYNAMEDIALOG_H
