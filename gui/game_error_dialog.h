#ifndef GAME_ERROR_DIALOG_H
#define GAME_ERROR_DIALOG_H

#include <QDialog>

namespace Ui {
class GameErrorDialog;
}

class GameErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameErrorDialog(QString errorMessage, QWidget *parent = 0);
    ~GameErrorDialog();

private:
    Ui::GameErrorDialog *ui;
};

#endif // GAME_ERROR_DIALOG_H
