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

class IInfoWidget: public QWidget, public Observer {
protected:
	Player* player;
	MapScene* scene;
	std::vector<IAttribute*> attributes;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *subMainLayout = new QHBoxLayout;
	QVBoxLayout *nameLayout = new QVBoxLayout;
	QVBoxLayout *valueLayout = new QVBoxLayout;
	QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
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

