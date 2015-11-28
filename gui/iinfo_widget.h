#ifndef IINFO_WIDGET
#define IINFO_WIDGET
#include <QWidget>
#include <vector>
#include <QWidget>
#include "map_scene.h"
#include "player.h"
#include "observer.h"
#include "iattribute.h"
class IInfoWidget: public QWidget, public Observer{
protected:
	std::vector<IAttribute*> attributes;

public:
	virtual void addAttribute(IAttribute* attribute);
	virtual std::vector<IAttribute*> getAttributes();
	virtual void draw();
	virtual void observedUpdated();
	virtual Player* getPlayer();
	virtual MapScene* getScene();
	virtual QWidget* getParent();
};

#endif // IINFO_WIDGET

