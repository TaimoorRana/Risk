#include "info_widget.h"
#include "army_attribute.h"
InfoWidget::InfoWidget(Player *subject, MapScene *scene, QWidget *parent)
{
	this->player = subject;
	this->scene = scene;
	player->attachObserver(this);
	ArmyAttribute* r = new ArmyAttribute(subject);
	addAttribute(r);
	draw();
}

void InfoWidget::observedUpdated()
{
	std::vector<IAttribute*>::iterator it;
	foreach (QWidget * w, valueLayout->findChildren<QWidget*>()) delete w;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		valueLayout->addWidget((*it)->getValue());
	}
}

