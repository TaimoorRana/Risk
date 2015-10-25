#include "gameboardview.h"
#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QVariant>

GameBoardView::GameBoardView() :
    QWidget()
{
    resize(650,450);
    //can reset size
    //may need to delete this
    QLabel *riskGame = new QLabel("Welcome To Risk Game");
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(riskGame);
    comboBox= new QComboBox();
    comboBox->addItem(("1"));
    comboBox->addItem(("2"));
    comboBox->addItem(("3"));
    comboBox->addItem(("4"));
    comboBoxLabel = new QLabel("Number of Players");
    mainLayout->addWidget(comboBoxLabel);
    mainLayout->addWidget(comboBox);

    beginGameButton = new QPushButton(this);
    beginGameButton->setText("submit");
    mainLayout->addWidget(beginGameButton);
    connect(beginGameButton,SIGNAL(clicked()),this,SLOT(beginGame()));




}
void GameBoardView::beginGame(){
    if(gameBegun){
        qDebug() << "Button Clicked ";
    }
    else{
        gameBegun = true;
        qDebug() << "Button Clicked ";
        //check if widget exists
        numberOfPlayers = comboBox->currentText().toInt();
        qDebug() << "Button Clicked "<<numberOfPlayers;
        mainLayout->removeWidget(comboBoxLabel);
        delete comboBoxLabel;
        mainLayout->removeWidget(comboBox);
        delete comboBox;
        mainLayout->removeWidget(beginGameButton);
        beginGameButton->setVisible(false);
        //delete beginGameButton;
        /*delete comboBox;
        delete beginGameButton;
        delete comboBoxLabel;*/
        //how to get int to string
        gameBeganLabel = new QLabel("Your Game has begin");

        mainLayout->addWidget(gameBeganLabel);
    }



}
void GameBoardView::endOfGame(){

}
//destructor
GameBoardView::~GameBoardView(){

}
