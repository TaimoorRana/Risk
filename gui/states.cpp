#include "states.h"


void States:: setState(playPhase newState)
{
    emit stateChanged(newState);
    emit testSignal();
}

