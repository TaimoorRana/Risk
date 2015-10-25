#include "continent.h"
#include "debug.h"
#include <iostream>

Continent::Continent(const std::string& name): name(name) { }
Continent::Continent(const Continent& continent) { name = continent.name;}
std::string Continent::getNameContinent() const { return this->name;}
void Continent::setNameContinent(const std::string& name) {	this->name = name;}
