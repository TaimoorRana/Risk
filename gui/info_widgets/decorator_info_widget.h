#ifndef DECORATOR_INFO_WIDGET
#define DECORATOR_INFO_WIDGET
#include "iinfo_widget.h"
class DecoratorInfoWidget: public IInfoWidget {
protected:
	IInfoWidget* baseInfoWidget;
public:
	DecoratorInfoWidget(IInfoWidget* infoWidget);
	void observedUpdated();
};

#endif // DECORATOR_INFO_WIDGET

