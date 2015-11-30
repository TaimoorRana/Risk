#include "decorator_info_widget.h"

DecoratorInfoWidget::DecoratorInfoWidget(IInfoWidget *infoWidget)
{
	attributes = infoWidget->getAttributes();
	this->player = infoWidget->getPlayer();
	this->scene = infoWidget->getScene();
	player->attachObserver(this);
}

void DecoratorInfoWidget::observedUpdated()
{
	std::vector<IAttribute*>::iterator it;
	foreach (QWidget * w, valueLayout->findChildren<QWidget*>()) delete w;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		valueLayout->addWidget((*it)->getValue());
	}
}
