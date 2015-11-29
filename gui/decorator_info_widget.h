#ifndef DECORATOR_INFO_WIDGET
#define DECORATOR_INFO_WIDGET
#include "iinfo_widget.h"
class DecoratorInfoWidget: public IInfoWidget{
protected:
	IInfoWidget* baseInfoWidget;
};

#endif // DECORATOR_INFO_WIDGET

