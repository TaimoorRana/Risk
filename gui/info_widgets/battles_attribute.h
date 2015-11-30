#ifndef BATTLES_ATTRIBUTE_H
#define BATTLES_ATTRIBUTE_H
#include "iattribute.h"

class BattlesAttribute: public IAttribute{
public:
	BattlesAttribute(Player* player);
	void observedUpdated();
};

#endif // BATTLES_ATTRIBUTE_H

