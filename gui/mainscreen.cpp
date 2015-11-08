#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

MainScreen::MainScreen(RiskMap *map, QWidget *parent) :QMainWindow(parent), ui(new Ui::MainScreen)
{
    ui->setupUi(this);
//    nameDialog = new PlayerNameDialog(this); //This does not make a dialog window appear.
    this->map = map;
    setupPlayers();
    setMouseTracking(true);
    ui->attackRadio->setChecked(true);
}

void MainScreen::setupPlayers(){
    std::unordered_map<std::string,Player> players = map->getPlayers();
    std::unordered_map<std::string,Player>::iterator playerIterator;
    for(playerIterator = players.begin(); playerIterator != players.end(); playerIterator++){
        ui->Player1->setText(QString::fromStdString((playerIterator->second).getName()));
    }
}

void MainScreen::mousePressEvent(QMouseEvent *e){
    qDebug() <<e->pos().x();
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::on_pushButton_clicked()
{
    if(ui->attackRadio->isChecked()){
        ui->reinforcementRadio->setChecked(true);
        return;
    }else if(ui->fortifyRadio->isChecked()){
        ui->attackRadio->setChecked(true);
        
        return;
    }else{
        
        ui->fortifyRadio->setChecked(true);
        return;
    }
}
