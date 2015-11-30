#ifndef CONTINENT_ATTRIBUTE
#define CONTINENT_ATTRIBUTE
#include "iattribute.h"
class ContinentAttribute: public IAttribute{
public:
	ContinentAttribute(Player* player);
	void observedUpdated();
};

#endif // CONTINENT_ATTRIBUTE

