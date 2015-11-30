#include "info_widget.h"
InfoWidget::InfoWidget(Player *subject, MapScene *scene, QWidget *parent)
{
	this->player = subject;
	this->scene = scene;
	player->attachObserver(this);
	ArmyAttribute* army = new ArmyAttribute(subject);
	CardAttribute* card =  new CardAttribute(subject);
	CountryAttribute* country = new CountryAttribute(subject);
	addAttribute(army);
	addAttribute(card);
	addAttribute(country);
	draw();
}

InfoWidget::~InfoWidget()
{
	player->detachObserver(this);
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

