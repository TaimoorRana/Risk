#ifndef PLAYERSUBJECT
#define PLAYERSUBJECT
#include "player_observer.h"
class PlayerSubject{
public:
	/**
	 * @brief registerObserver
	 * @param observer
	 */
	virtual void registerObserver(PlayerObserver* observer) = 0;
	/**
	 * @brief unregisterObserver
	 * @param observer
	 */
	virtual void unregisterObserver(PlayerObserver* observer) = 0;
	/**
	 * @brief notifyObserver updates all the observers
	 */
	virtual void notifyObserver() = 0;
};

#endif // PLAYERSUBJECT

