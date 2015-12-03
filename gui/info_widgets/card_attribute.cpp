#include "card_attribute.h"

CardAttribute::CardAttribute(Player *player)
{
	this->player = player;
	name = new QLabel(QString::fromStdString("Cards:"));
    value = new QLabel(QString::number(player->getCards()));
	value->setAlignment(Qt::AlignRight);
}

void CardAttribute::observedUpdated()
{
    value->setText(QString::number(player->getCards()));
}
