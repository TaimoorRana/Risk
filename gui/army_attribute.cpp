#include "army_attribute.h"

ArmyAttribute::ArmyAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Army:"));
	this->value = new QLabel(QString::number(player->getReinforcements()));
	this->value->setAlignment(Qt::AlignRight);
}

void ArmyAttribute::observedUpdated()
{
	this->value->setText(QString::number(player->getTotalArmy()));
}
