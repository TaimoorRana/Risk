#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
	virtual void observedUpdated() = 0;
	virtual ~Observer(){}
protected:
	Observer() {};
};

#endif // OBSERVER_H
