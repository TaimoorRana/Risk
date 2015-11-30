#ifndef IATTRIBUTE
#define IATTRIBUTE

#include <QLabel>
#include <QString>
#include "observer.h"
#include "player.h"
#include "game_driver.h"
#include "risk_map.h"
class IAttribute: public Observer {
protected:
	QLabel* name;
	QLabel* value;
	Player* player = nullptr;
	RiskMap* map = GameDriver::getInstance()->getRiskMap();

public:
	virtual void observedUpdated() = 0;
	virtual QLabel* getName();
	virtual QLabel* getValue();
};

#endif // IATTRIBUTE
