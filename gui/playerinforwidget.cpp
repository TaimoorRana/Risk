#include "playerinforwidget.h"
#include "ui_playerinforwidget.h"

PlayerInforWidget::PlayerInforWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInforWidget)
{
    ui->setupUi(this);
}

PlayerInforWidget::~PlayerInforWidget()
{
    delete ui;
}
