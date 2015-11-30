#include "army_attribute.h"

ArmyAttribute::ArmyAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Army:"));
	value = new QLabel(QString::number(player->getReinforcements()));
	value->setAlignment(Qt::AlignRight);
}

void ArmyAttribute::observedUpdated()
{
	value->setText(QString::number(player->getReinforcements()));
}
