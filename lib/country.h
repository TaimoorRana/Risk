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
public:
    Country():name(""){}
    Country(const std::string& name);
    Country(const Country& country);
	std::string getName() const;
	void setName(std::string name);
};
#endif // COUNTRY_H
