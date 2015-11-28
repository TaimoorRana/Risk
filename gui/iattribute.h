#ifndef IATTRIBUTE
#define IATTRIBUTE

#include <QLabel>
#include <QString>
#include "observer.h"
#include "player.h"
class IAttribute: public Observer {

public:
	virtual void observedUpdated() = 0;
	virtual QLabel* getName() = 0;
	virtual QLabel* getValue() = 0;
};

#endif // IATTRIBUTE
