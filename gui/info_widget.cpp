#include "info_widget.h"
#include "reinforcement_attribute.h"
InfoWidget::InfoWidget(Player *subject, MapScene *scene, QWidget *parent)
{
	this->player = subject;
	this->scene = scene;
	player->attachObserver(this);
	ReinforcementAttribute* r = new ReinforcementAttribute(subject);
	ReinforcementAttribute* r2 = new ReinforcementAttribute(subject);
	addAttribute(r);
	addAttribute(r2);
	draw();
}
void InfoWidget::addAttribute(IAttribute *attribute)
{
	attributes.push_back(attribute);
}

std::vector<IAttribute *> InfoWidget::getAttributes()
{
	return this->attributes;
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

Player *InfoWidget::getPlayer()
{
	return this->player;
}

MapScene *InfoWidget::getScene()
{
	return this->scene;
}

QWidget *InfoWidget::getParent()
{
	return this->getParent();
}
