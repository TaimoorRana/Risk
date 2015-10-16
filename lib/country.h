#ifndef LIB_COUNTRY_H
#define LIB_COUNTRY_H

#include <string>
#include <vector>
#include "continent.h"

class Continent; //forward declaration

class Country {
private:
	std::string name;
	Continent* continent;
	int x;
	int y;
	std::vector<Country*> neighbours;

public:
	Country(std::string name, Continent continent, int x, int y);
	std::string getName();
	void setName(std::string name);
	Continent* getContinent();
	void setContinent(Continent* continent);
	int getPositionX();
	void setPositionX(int x);
	int getPositionY();
	void setPositionY(int y);
	std::vector<Country*> getNeighbours();
	void addNeighbour(Country* country);
};
#endif // LIB_COUNTRY_H
