#ifndef GAMEBOARDVIEW_H
#define GAMEBOARDVIEW_H
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QString>
#include <QComboBox>
#include <QWidget>
#include <QMenuBar>
#include <string>

class GameBoardView:public QWidget
{
    Q_OBJECT
public:
    //note explict GameBoardView(*dd)
    GameBoardView();
    //does it need to be virtual
    virtual ~GameBoardView();
    //GameBoardView();
    QLabel *currentPlayerTurn;
    //may need outside qLabel and combobox later
    void turns();
    void endOfTurn();
private:
    // main layout
    QVBoxLayout *mainLayout;
    // grid layout of board
    QGridLayout *boardLayout;
    QPushButton *beginGameButton;
    QPushButton *reinforce;
    QPushButton *attack;
    QPushButton *move;
    QLabel *selectPlayers;
    QComboBox *comboBox;
    QLabel *comboBoxLabel;
    QLabel *gameBeganLabel;
    QMenuBar *gameMenu;
    //string *numberOfPlayersString;
    bool gameBegun=false;
    int numberOfPlayers;
    //will for future turn into players
    int *arrayOfPlayers;
    QLabel *attackLabel;
    QLabel *moveLabel;
    QLabel *reinforceLabel;
    QAction *reinforceAction;
    QAction *moveAction;
    QAction *attackAction;
    QAction *endTurnAction;
    int turnNumber;
    //slot for each possibili


public  slots:
    void beginGame();
    void endOfGame();
    void attackPhase();
    void reinforcePhase();
    void movePhase();
    void endTurn();
};

#endif // GAMEBOARDVIEW_H
