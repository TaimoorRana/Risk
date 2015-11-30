#include "battle_won_attribute.h"

BattleWonAttribute::BattleWonAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Battles Won:"));
	this->value = new QLabel(QString::number(player->getBattlesWon()));
	this->value->setAlignment(Qt::AlignRight);
}

void BattleWonAttribute::observedUpdated()
{
	this->value->setText(QString::number(player->getBattlesWon()));
}
