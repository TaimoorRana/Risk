#ifndef PLAYERSUBJECT
#define PLAYERSUBJECT
#include "player_observer.h"
class PlayerSubject{
public:
	virtual void registerObserver(PlayerObserver*) = 0;
	virtual void unregisterObserver(PlayerObserver*) = 0;
	virtual void notifyObserver() = 0;
};

#endif // PLAYERSUBJECT

