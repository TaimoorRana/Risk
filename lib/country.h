#ifndef LIB_COUNTRY_H
#define LIB_COUNTRY_H

#include <string>
#include <vector>
#include "continent.h"

class Continent; //forward declaration

class Country {
private:
	std::string name;
	std::string continent_name;
	int x;
	int y;
	std::vector<Country> neighbours;

public:
	Country(std::string name, std::string continent, int x, int y);
	Country(const Country& country);
	std::string getName() const;
	void setName(std::string name);
	std::string getContinent() const;
	void setContinent(const std::string& continent_name);
	int getPositionX() const;
	void setPositionX(int x);
	int getPositionY() const;
	void setPositionY(int y);
	std::vector<Country> getNeighbours() const;
	void addNeighbour(Country country);
};
#endif // LIB_COUNTRY_H
