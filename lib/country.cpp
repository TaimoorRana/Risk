#include "country.h"
#include "debug.h"

Country::Country(const std::string& name) {
    this->setName(name);
}

Country::Country(Country const& country) {
	name = country.name;
}


std::string Country::getName() const {
	return this->name;
}
void Country::setName(const std::string name) {
	this->name = name;
}


