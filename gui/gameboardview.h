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

class GameBoardView:public QWidget
{
    Q_OBJECT
public:
    //note explict GameBoardView(*dd)
     GameBoardView();
    //does it need to be virtual
    virtual ~GameBoardView();
    //GameBoardView();
    QLabel *currentPlayer;
//may need outside qLabel and combobox later
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
    bool gameBegun=false;
    int numberOfPlayers;
    //slot for each possibili


public  slots:
    void beginGame();
    void endOfGame();
};

#endif // GAMEBOARDVIEW_H
