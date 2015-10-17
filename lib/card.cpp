#include "card.h"

Card::Card() {}
Card::Card(const Card& card) {
	name = card.name;
}

std::string Card::getName() {
	return this->name;
}
void Card::setName(const std::string& name) {
	this->name = name;
}
