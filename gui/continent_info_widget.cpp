#include "continent_info_widget.h"

ContinentInfoWidget::ContinentInfoWidget(IInfoWidget *infoWidget): DecoratorInfoWidget(infoWidget)
{
	ContinentAttribute* continent = new ContinentAttribute(player);
	addAttribute(continent);
	draw();
}

