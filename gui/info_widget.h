#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"
#include <QSpacerItem>
class InfoWidget:public IInfoWidget, public Observer{


public:
	InfoWidget( Player *subject, MapScene* scene,QWidget *parent = 0);
	void addAttribute(IAttribute* attribute);
	std::vector<IAttribute*> getAttributes();
	void observedUpdated();
	Player* getPlayer();
	MapScene* getScene();
	QWidget* getParent();
};

#endif // INFO_WIDGET

