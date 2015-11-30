#ifndef COUNTRY_ATTRIBUTE
#define COUNTRY_ATTRIBUTE
#include "iattribute.h"

class CountryAttribute: public IAttribute{
public:
	CountryAttribute(Player* player);
	void observedUpdated();
};

#endif // COUNTRY_ATTRIBUTE

