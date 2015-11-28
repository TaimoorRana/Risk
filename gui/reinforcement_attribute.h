#ifndef REINFORCEMENT_ATTRIBUTE
#define REINFORCEMENT_ATTRIBUTE
#include "iattribute.h"
class ReinforcementAttribute: public IAttribute {
private:
	QLabel* name;
	QLabel* value;
	Player* player = nullptr;
public:
	ReinforcementAttribute(Player* player);
	void observedUpdated();
	QLabel* getName();
	QLabel* getValue();
};

#endif // REINFORCEMENT_ATTRIBUTE
