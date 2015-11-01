#ifndef STATES_H
#define STATES_H
#include <QtCore>

class States:public QObject
{
    Q_OBJECT
    Q_ENUMS(state)
public:
    States();
    enum playPhase{ REINFORCE,ATTACK,MOVE};
    void setState(States::playPhase newState);

signals:
    void stateChanged(States::playPhase newState);
    void testSignal(void);

};

#endif // STATES_H
