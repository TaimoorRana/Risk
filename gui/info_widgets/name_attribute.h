#ifndef NAME_ATTRIBUTE_H
#define NAME_ATTRIBUTE_H
#include "iattribute.h"
class NameAttribute: public IAttribute{
public:
	NameAttribute(Player* player);
	void observedUpdated();
};

#endif // NAME_ATTRIBUTE_H

