#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>
#include <vector>
#include "continent.h"

class Continent; //forward declaration
class Player; //forward declaration

class Country {
private:
	std::string name;
	Continent* continent;

public:
	Country(std::string name, Continent continent, int x, int y);
	Country(const Country& country);
	std::string getName() const;
	void setName(std::string name);
	Continent getContinent() const;
	void setContinent(Continent continent);

};
#endif // COUNTRY_H
