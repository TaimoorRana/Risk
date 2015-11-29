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
class IInfoWidget: public QWidget{
protected:
	Player* player;
	MapScene* scene;
	std::vector<IAttribute*> attributes;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *subMainLayout = new QHBoxLayout;
	QVBoxLayout *nameLayout = new QVBoxLayout;
	QVBoxLayout *valueLayout = new QVBoxLayout;
	QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	virtual void addAttribute(IAttribute* attribute) = 0;
	virtual std::vector<IAttribute*> getAttributes() = 0;
	void draw();
	virtual void observedUpdated() = 0;
	virtual Player* getPlayer() = 0;
	virtual MapScene* getScene() = 0;
	virtual QWidget* getParent() = 0;
};

#endif // IINFO_WIDGET

