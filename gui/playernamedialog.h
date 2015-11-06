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

private:
    Ui::PlayerNameDialog *ui;
};

#endif // PLAYERNAMEDIALOG_H
