#ifndef IATTRIBUTE
#define IATTRIBUTE

#include <QLabel>
#include <QString>
#include "observer.h"
#include "player.h"
class IAttribute: public Observer {
protected:
	QLabel* name;
	QLabel* value;
	Player* player = nullptr;
public:
	virtual void observedUpdated() = 0;
	virtual QLabel* getName();
	virtual QLabel* getValue();
};

#endif // IATTRIBUTE
