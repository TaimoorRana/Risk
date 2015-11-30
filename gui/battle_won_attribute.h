#ifndef BATTLE_WON_ATTRIBUTE
#define BATTLE_WON_ATTRIBUTE
#include "iattribute.h"

class BattleWonAttribute: public IAttribute{
public:
	BattleWonAttribute(Player* player);
	void observedUpdated();
};

#endif // BATTLE_WON_ATTRIBUTE

