#include "country_attribute.h"

CountryAttribute::CountryAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Countries:"));
	this->value = new QLabel(QString::number(player->getCountriesOwned().size()));
	this->value->setAlignment(Qt::AlignRight);
}

void CountryAttribute::observedUpdated()
{
	this->value->setText(QString::number(player->getCountriesOwned().size()));
}
