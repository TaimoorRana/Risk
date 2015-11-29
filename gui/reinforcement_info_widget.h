#ifndef REINFORCEMENT_INFO_WIDGET
#define REINFORCEMENT_INFO_WIDGET
#include "decorator_info_widget.h"
class ReinforcementInfoWidget: public DecoratorInfoWidget, public Observer{
public:
	ReinforcementInfoWidget(IInfoWidget *infoWiget);
	void observedUpdated();
};

#endif // REINFORCEMENT_INFO_WIDGET

