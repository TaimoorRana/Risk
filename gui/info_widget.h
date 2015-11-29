#ifndef INFO_WIDGET
#define INFO_WIDGET
#include "iinfo_widget.h"
#include <QSpacerItem>
class InfoWidget:public QWidget, public Observer{
private:
	Player* player;
	MapScene* scene;
	std::vector<IAttribute*> attributes;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *subMainLayout = new QHBoxLayout;
	QVBoxLayout *nameLayout = new QVBoxLayout;
	QVBoxLayout *valueLayout = new QVBoxLayout;
	QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

public:
	InfoWidget(QWidget *parent, Player *subject, MapScene* scene);
	void addAttribute(IAttribute* attribute);
	std::vector<IAttribute*> getAttributes();
	void draw();
	void observedUpdated();
	Player* getPlayer();
	MapScene* getScene();
	QWidget* getParent();
};

#endif // INFO_WIDGET

