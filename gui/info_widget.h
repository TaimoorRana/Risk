#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"
#include "country_attribute.h"
#include "card_attribute.h"
#include "army_attribute.h"
class InfoWidget:public IInfoWidget, public Observer{


public:
	InfoWidget( Player *subject, MapScene* scene,QWidget *parent = 0);
	~InfoWidget();
	void observedUpdated();
};

#endif // INFO_WIDGET

