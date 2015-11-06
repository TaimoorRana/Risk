#include "playernamedialog.h"
#include "ui_playernamedialog.h"

PlayerNameDialog::PlayerNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerNameDialog)
{
    ui->setupUi(this);
}

PlayerNameDialog::~PlayerNameDialog()
{
    delete ui;
}

QString PlayerNameDialog::getText()
{
    return ui->lineEdit->text();
}
