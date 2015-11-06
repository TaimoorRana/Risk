#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QTimer>

MainScreen::MainScreen(RiskMap *map, QWidget *parent) :QMainWindow(parent), ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    nameDialog = new PlayerNameDialog(this);
    this->map = map;
    setupPlayers();
    //QTimer::singleShot(3000,nameDialog,SLOT(show()));
}

void MainScreen::setupPlayers(){
    ui->Player1->setText("Taimoor");
    ui->Player2->setText("Adrianna");
}

MainScreen::~MainScreen()
{
    delete ui;
}
