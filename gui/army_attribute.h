#ifndef ARMY_ATTRIBUTE
#define ARMY_ATTRIBUTE
#include "iattribute.h"
class ArmyAttribute: public IAttribute{
public:
	ArmyAttribute(Player* player);
	void observedUpdated();
};

#endif // ARMY_ATTRIBUTE

