#include "game_error_dialog.h"
#include "ui_game_error_dialog.h"

GameErrorDialog::GameErrorDialog(QString errorMessage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameErrorDialog)
{
    this->setModal(true); //Will make window be persistent on top.
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Error"));
    ui->errorMessageLabel->setText(errorMessage);
}

GameErrorDialog::~GameErrorDialog()
{
    delete ui;
}
