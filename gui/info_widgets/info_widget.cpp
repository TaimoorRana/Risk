#include "army_attribute.h"
#include "battles_attribute.h"
#include "info_widget.h"
#include "card_attribute.h"
#include "continent_attribute.h"
#include "country_attribute.h"
#include "name_attribute.h"
#include "reinforcement_attribute.h"


InfoWidget::InfoWidget(Player *subject, MapScene *scene, QWidget *parent)
{
	this->player = subject;
	this->scene = scene;
	player->attachObserver(this);
	NameAttribute* name = new NameAttribute(subject);
	ArmyAttribute* army = new ArmyAttribute(subject);
	BattlesAttribute* battles =  new BattlesAttribute(subject);
	CardAttribute* card =  new CardAttribute(subject);
	CountryAttribute* country = new CountryAttribute(subject);
	ContinentAttribute* continent = new ContinentAttribute(subject);
	ReinforcementAttribute* reinforcement = new ReinforcementAttribute(subject);

	addAttribute(name);
	addAttribute(reinforcement);
	addAttribute(army);
	addAttribute(card);
	addAttribute(country);
	addAttribute(continent);
	addAttribute(battles);

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

