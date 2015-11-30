#ifndef CARD_ATTRIBUTE
#define CARD_ATTRIBUTE
#include "iattribute.h"

class CardAttribute: public IAttribute{
public:
	CardAttribute(Player* player);
	void observedUpdated();
};

#endif // CARD_ATTRIBUTE

