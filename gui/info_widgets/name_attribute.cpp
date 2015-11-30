#include <set>
#include <string>
#include "name_attribute.h"
#include "game_driver.h"

NameAttribute::NameAttribute(Player *player)
{
	this->player = player;
	this->name = new QLabel(QString::fromStdString("Name:"));
	value = new QLabel(QString::number(0));
	value->setAlignment(Qt::AlignRight);

	this->observedUpdated();
}

void NameAttribute::observedUpdated()
{
	GameDriver* driver = GameDriver::getInstance();
	std::string playerName = player->getName();
	if (driver->getCurrentPlayerName() == playerName) {
		playerName = "<b>" + playerName + "</b>";
	}
	value->setText(QString::fromStdString(playerName));
}
