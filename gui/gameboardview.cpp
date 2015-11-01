#include <QComboBox>
#include <QLabel>
#include <QDebug>
#include <QVariant>
#include <QMenuBar>
#include <QAction>
#include <string>
#include <QString>
#include "gameboardview.h"
using namespace std;
/**
 * @brief GameBoardView::GameBoardView
 * Creates the GameBoard using stub functions to select number of players.
 */

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
/**
 * @brief GameBoardView::beginGame
 * begins The game inits the number of players and new gui view and the
 * game ordering.
 */
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
        //string playersString=std::string(itoa(numberOfPlayers));
        string playersString=std::to_string(numberOfPlayers);
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

        //QString *gameBegun= new QString("Your Game has begun");
        //gameBegun->append(playersString);
        gameBeganLabel = new QLabel((QString("Your Game has begun Players:%1").arg(1)));
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
/**
 * @brief GameBoardView::endOfGame
 * at end of game
 */
void GameBoardView::endOfGame(){

}
/**
 * @brief GameBoardView::~GameBoardView
 * default destructor
 */
GameBoardView::~GameBoardView(){

}
/**
 * @brief GameBoardView::movePhase
 * implements the move phase described in the game using enums.
 */
void GameBoardView:: movePhase(){
    if(currentMode == moveMode){
        moveLabel = new QLabel ("Moving turn ended select endOfTurn");
        mainLayout->addWidget(moveLabel);
        currentMode = endOfTurnMode;
    }

}
/**
 * @brief GameBoardView::reinforcePhase
 * implements the reinforcePhase described in the game using enums.
 */
void GameBoardView::reinforcePhase(){
    if(currentMode==reinforceMode){
        reinforceLabel = new QLabel ("Reinforce has been processed now please go to  attackPhase");
        mainLayout->addWidget(reinforceLabel);
        currentMode = attackMode;
    }

}
/**
 * @brief GameBoardView::attackPhase
 * implements the attackPhase.
 */
void GameBoardView::attackPhase(){
    if(currentMode==attackMode){
        attackLabel = new QLabel("Attack phase has been processed now please go to movePhase ");
        mainLayout->addWidget(attackLabel);
        currentMode = moveMode;
    }

}
/**
 * @brief GameBoardView::endTurn
 *  End of turn removes all the information about the previous turn and now allows current playersTurn.
 * Indicates the current players turn.
 */
void GameBoardView::endTurn(){
    if(currentMode ==endOfTurnMode){
        mainLayout->removeWidget(reinforceLabel);
        delete reinforceLabel;
        mainLayout->removeWidget(attackLabel);
        delete attackLabel;
        mainLayout->removeWidget(moveLabel);
        delete moveLabel;
        turnNumber++;
        if (turnNumber>numberOfPlayers){
            turnNumber =1;
        }
        currentMode = reinforceMode;
        mainLayout->removeWidget(gameBeganLabel);
        delete gameBeganLabel;
        gameBeganLabel = new QLabel((QString("Your Game has begun Players:%1").arg(turnNumber)));
        mainLayout->addWidget(gameBeganLabel);
    }


}

