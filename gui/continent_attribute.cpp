#include "continent_attribute.h"

ContinentAttribute::ContinentAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Continents:"));
	this->value = new QLabel(QString::number(map->getContinentsOwnedByPlayer(player->getName()).size()));
	this->value->setAlignment(Qt::AlignRight);
}

void ContinentAttribute::observedUpdated()
{
	this->value->setText(QString::number(map->getContinentsOwnedByPlayer(player->getName()).size()));
}

