#include "reinforcement_info_widget.h"
#include "reinforcement_attribute.h"
ReinforcementInfoWidget::ReinforcementInfoWidget(IInfoWidget *infoWiget)
{
	attributes = infoWiget->getAttributes();
	this->player = infoWiget->getPlayer();
	this->scene = infoWiget->getScene();
	player->attachObserver(this);
	ReinforcementAttribute* r = new ReinforcementAttribute(player);
	addAttribute(r);
	draw();
}

void ReinforcementInfoWidget::observedUpdated()
{
	std::vector<IAttribute*>::iterator it;
	foreach (QWidget * w, valueLayout->findChildren<QWidget*>()) delete w;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		valueLayout->addWidget((*it)->getValue());
	}
}
