#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"

class InfoWidget: public IInfoWidget {
public:
	InfoWidget(Player *subject, MapScene* scene, QWidget *parent = 0);
	~InfoWidget();
	void observedUpdated();
};

#endif // INFO_WIDGET

