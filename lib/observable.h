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
    virtual void detachAllObservers();
	virtual void setNotificationsEnabled(bool enabled);
	virtual bool getNotificationsEnabled();
	virtual void notifyObservers() const;
	Observable();
protected:
	bool notifyEnabled = true;
	std::list<Observer*> observers;
};

#endif // OBSERVABLE_H
