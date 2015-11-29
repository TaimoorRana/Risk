#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"
#include <QSpacerItem>
class InfoWidget:public IInfoWidget, public Observer{


public:
	InfoWidget( Player *subject, MapScene* scene,QWidget *parent = 0);
	void observedUpdated();
};

#endif // INFO_WIDGET

