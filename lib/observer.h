#ifndef OBSERVER_H
#define OBSERVER_H
#include "observable.h"

// Forward declaration due to circular dependency
class Observable;

class Observer {
public:
	~Observer() {};
	virtual void observedUpdated() = 0;
protected:
	Observer() {};
};

#endif // OBSERVER_H
