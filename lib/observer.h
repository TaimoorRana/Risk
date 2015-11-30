#ifndef OBSERVER_H
#define OBSERVER_H
#include "observable.h"

// Forward declaration due to circular dependency
class Observable;


class Observer {
public:
	virtual void observedUpdated() = 0;
    virtual ~Observer(){}
protected:
	Observer() {};
};

#endif // OBSERVER_H
