#ifndef CONTINENT_INFO_WIDGET
#define CONTINENT_INFO_WIDGET
#include "decorator_info_widget.h"
#include "continent_attribute.h"
class ContinentInfoWidget: public DecoratorInfoWidget{
public:
	ContinentInfoWidget(IInfoWidget *infoWidget);
};

#endif // CONTINENT_INFO_WIDGET

