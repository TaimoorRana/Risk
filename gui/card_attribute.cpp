#include "card_attribute.h"

CardAttribute::CardAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Cards:"));
	this->value = new QLabel(QString::number(0));
	this->value->setAlignment(Qt::AlignRight);
}

void CardAttribute::observedUpdated()
{
	this->value->setText(QString::number(0));
}
