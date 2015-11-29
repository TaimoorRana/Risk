#ifndef REINFORCEMENT_ATTRIBUTE
#define REINFORCEMENT_ATTRIBUTE
#include "iattribute.h"
class ReinforcementAttribute: public IAttribute {
public:
	ReinforcementAttribute(Player* player);
	void observedUpdated();
};

#endif // REINFORCEMENT_ATTRIBUTE
