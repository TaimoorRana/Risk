#include "reinforcement_info_widget.h"
#include "reinforcement_attribute.h"
ReinforcementInfoWidget::ReinforcementInfoWidget(IInfoWidget *infoWiget): DecoratorInfoWidget(infoWiget)
{
	ReinforcementAttribute* r = new ReinforcementAttribute(player);
	addAttribute(r);
	draw();
}
