#ifndef PLAYERNAMEDIALOG_H
#define PLAYERNAMEDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class PlayerNameDialog;
}

class PlayerNameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlayerNameDialog(QWidget *parent = 0);
    ~PlayerNameDialog();
    QString getText();

private slots:
    void on_buttonBox_accepted();


private:
    Ui::PlayerNameDialog *ui;
    const int totalCPU = 4;
    void setComboBox();
};

#endif // PLAYERNAMEDIALOG_H
