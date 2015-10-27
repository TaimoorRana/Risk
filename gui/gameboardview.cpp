
#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QVariant>
#include <QMenuBar>
#include <QAction>
#include <string>
#include "gameboardview.h"

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
    currentMode = reinforceMode;
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
        turnNumber =1;
        gameBegun = true;
        qDebug() << "Button Clicked ";
        //check if widget exists
        numberOfPlayers = comboBox->currentText().toInt();
        //char *intstr = itoa(numberOfPlayers);
       // numberOfPlayersString = string(intstr);
        arrayOfPlayers = new int[numberOfPlayers];
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

        gameBeganLabel = new QLabel("Your Game has begun");
        gameMenu = new QMenuBar(0);
        //reinforce attack, move
        reinforceAction = new QAction("reinforce",this);
        connect (reinforceAction,SIGNAL(triggered()),this,SLOT(reinforcePhase()));
        attackAction = new QAction("attack",this);\
        connect (attackAction,SIGNAL(triggered()),this,SLOT(attackPhase()));
        moveAction = new QAction("move",this);
        connect (moveAction,SIGNAL(triggered()),this,SLOT(movePhase()));
        endTurnAction = new QAction ("endTurn", this);
        connect(endTurnAction,SIGNAL(triggered()),this,SLOT(endTurn()));
        gameMenu->addAction(reinforceAction);
        gameMenu->addAction(attackAction);
        gameMenu->addAction(moveAction);
        gameMenu->addAction(endTurnAction);
        mainLayout->addWidget(gameMenu);

        mainLayout->addWidget(gameBeganLabel);
    }



}
void GameBoardView::endOfGame(){

}
//destructor
GameBoardView::~GameBoardView(){

}
void GameBoardView:: movePhase(){
    if(currentMode == moveMode){
        moveLabel = new QLabel ("Moving turn ended select endOfTurn");
        mainLayout->addWidget(moveLabel);
        currentMode = endOfTurnMode;
    }

}
void GameBoardView::reinforcePhase(){
    if(currentMode==reinforceMode){
        reinforceLabel = new QLabel ("Reinforce has been processed now please go to  attackPhase");
        mainLayout->addWidget(reinforceLabel);
        currentMode = attackMode;
    }

}
void GameBoardView::attackPhase(){
    if(currentMode==attackMode){
        attackLabel = new QLabel("Attack phase has been processed now please go to movePhase ");
        mainLayout->addWidget(attackLabel);
        currentMode = moveMode;
    }

}
void GameBoardView::endTurn(){
    if(currentMode ==endOfTurnMode){
        mainLayout->removeWidget(reinforceLabel);
        delete reinforceLabel;
        mainLayout->removeWidget(attackLabel);
        delete attackLabel;
        mainLayout->removeWidget(moveLabel);
        delete moveLabel;
        turnNumber++;
        currentMode = reinforceMode;
    }


}

