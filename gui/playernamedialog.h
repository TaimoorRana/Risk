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
	QString* getText();
	QString* getChoice();

private slots:
    void on_buttonBox_accepted();


private:
    Ui::PlayerNameDialog *ui;
    const int totalCPU = 4;
    void setComboBox();
	QString* name;
	QString* choice;
};

#endif // PLAYERNAMEDIALOG_H
