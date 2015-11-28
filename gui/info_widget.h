#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"
class InfoWidget{

public:
	void addAttribute(IAttribute* attribute);
	std::vector<IAttribute*> getAttributes();
	void draw();
	void observedUpdated();
	Player* getPlayer();
	MapScene* getScene();
	QWidget* getParent();
};

#endif // INFO_WIDGET

