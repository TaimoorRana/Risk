#include "battles_attribute.h"

BattlesAttribute::BattlesAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Battles W/L:"));
	this->value = new QLabel("0/0");
	this->value->setAlignment(Qt::AlignRight);

	this->observedUpdated();
}

void BattlesAttribute::observedUpdated()
{
	QString numWon = QString::number(player->getBattlesWon());
	QString numLost = QString::number(player->getBattlesLost());
	this->value->setText(QString("%1/%2").arg(numWon, numLost));
}
