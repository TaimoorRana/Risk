#include <set>
#include <string>
#include "army_attribute.h"
#include "game_driver.h"
#include "risk_map.h"

ArmyAttribute::ArmyAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Armies:"));
	value = new QLabel(QString::number(0));
	value->setAlignment(Qt::AlignRight);

	this->observedUpdated();
}

void ArmyAttribute::observedUpdated()
{
	GameDriver* driver = GameDriver::getInstance();
	RiskMap* map = driver->getRiskMap();

	int armies = 0;
	for (auto countryName : map->getCountriesOwnedByPlayer(player->getName())) {
		armies += map->getCountry(countryName)->getArmies();
	}
	value->setText(QString::number(armies));
}
