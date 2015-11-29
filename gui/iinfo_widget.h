#ifndef IINFO_WIDGET
#define IINFO_WIDGET
#include <QWidget>
#include <vector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "map_scene.h"
#include "player.h"
#include "observer.h"
#include "iattribute.h"
class IInfoWidget{

public:
	virtual void addAttribute(IAttribute* attribute) = 0;
	virtual std::vector<IAttribute*> getAttributes() = 0;
	virtual void draw() = 0;
	virtual void observedUpdated() = 0;
	virtual Player* getPlayer() = 0;
	virtual MapScene* getScene() = 0;
	virtual QWidget* getParent() = 0;
};

#endif // IINFO_WIDGET

