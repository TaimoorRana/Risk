#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include <list>
#include "observer.h"

// Forward reference due to circular dependency
class Observer;

class Observable {
public:
	virtual void attachObserver(Observer* observer);
	virtual void detachObserver(Observer* observer);
	virtual void notifyObservers();
	Observable();
protected:
	std::list<Observer*> observers;
};

#endif // OBSERVABLE_H
