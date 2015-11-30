#include "iinfo_widget.h"

void IInfoWidget::draw()
{
	QColor playerColor = this->scene->getPlayerColor(this->player->getName());
	std::string hexColor = playerColor.name().toStdString();
	QLabel *colorLabel = new QLabel();
	colorLabel->setStyleSheet(QString::fromStdString("QLabel { background-color : " + hexColor + "; }"));
	mainLayout->addLayout(subMainLayout);
	subMainLayout->addWidget(colorLabel);
	subMainLayout->addLayout(nameLayout);
	subMainLayout->addLayout(valueLayout);
	subMainLayout->addItem(spacer);
	mainLayout->setSpacing(2);
	mainLayout->setContentsMargins(0,0,0,0);
	std::vector<IAttribute*>::iterator it;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		nameLayout->addWidget((*it)->getName());
		valueLayout->addWidget((*it)->getValue());
	}
	this->setLayout(mainLayout);
}

void IInfoWidget::addAttribute(IAttribute *attribute)
{
	attributes.push_back(attribute);
}

std::vector<IAttribute *> IInfoWidget::getAttributes()
{
	return this->attributes;
}



void IInfoWidget::observedUpdated()
{
	std::vector<IAttribute*>::iterator it;
	foreach (QWidget * w, valueLayout->findChildren<QWidget*>()) delete w;
	for(it = attributes.begin(); it != attributes.end(); it++)
	{
		valueLayout->addWidget((*it)->getValue());
	}
}

Player *IInfoWidget::getPlayer()
{
	return this->player;
}

MapScene *IInfoWidget::getScene()
{
	return this->scene;
}

QWidget *IInfoWidget::getParent()
{
	return this->getParent();
}
