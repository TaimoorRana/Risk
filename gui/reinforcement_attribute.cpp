#include "reinforcement_attribute.h"


ReinforcementAttribute::ReinforcementAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Reinforcements:"));
	this->value = new QLabel(QString::number(player->getReinforcements()));
	this->value->setAlignment(Qt::AlignRight);
}

void ReinforcementAttribute::observedUpdated()
{
	this->value->setText(QString::number(player->getReinforcements()));
}

QLabel* ReinforcementAttribute::getName()
{
	return name;
}

QLabel* ReinforcementAttribute::getValue()
{
	observedUpdated();
	return value;
}
