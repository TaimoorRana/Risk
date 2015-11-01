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

/**
 * @brief The GameBoardView class
 *  The gameboard view class which creates the GameBoardWidget and adds all the
 * widgets needed and deletes them accordingly when needed. Also implement all the stub functions for the GameBoard.
 *Reinforce Attack, move,endTurn
 */

class GameBoardView:public QWidget
{
    Q_OBJECT
public:

    GameBoardView();

    virtual ~GameBoardView();

    QLabel *currentPlayerTurn;

    void turns();
    void endOfTurn();
    enum Mode{reinforceMode,attackMode,moveMode, endOfTurnMode};
    Mode currentMode= reinforceMode;
private:

    QVBoxLayout *mainLayout;/**< MainLayout for the game */
    // grid layout of board
    QGridLayout *boardLayout;/**<SubLayout */
    //buttons added
    QPushButton *beginGameButton;/**<beginGameButton */
    QPushButton *reinforce;/**<reinforce */
    QPushButton *attack;/**<attackButton */
    QPushButton *move; /**<move Button */
    QLabel *selectPlayers; /**<Highliting which player to select Label */
    QComboBox *comboBox;
    QLabel *comboBoxLabel;
    QLabel *gameBeganLabel;
    QMenuBar *gameMenu;
    //check if the game has begun
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
