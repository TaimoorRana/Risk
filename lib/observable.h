#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include "observer.h"
#include <list>
using namespace std;

// Forward reference due to circular dependency
class Observer;

class Observable {
public:
	virtual void attachObserver(Observer* observer);
	virtual void detachObserver(Observer* observer);
	virtual void notifyObservers();
	Observable();
	~Observable() {};
private:
	list<Observer*> observers;
};

#endif // OBSERVABLE_H
