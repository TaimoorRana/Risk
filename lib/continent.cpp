#include "continent.h"
#include "debug.h"
#include <iostream>


Continent::Continent(const std::string& name): name(name) { }
Continent::Continent(const Continent& continent) { name = continent.name;}
Continent& Continent::operator = (const Continent& other){
	this->name = other.name;
	return *this;
}
std::string Continent::getName() const { return this->name;}
