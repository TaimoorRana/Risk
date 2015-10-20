#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>
#include <set>
#include <map>
#include "country.h"

class Country; // forward declaration

class Continent {
private:
	std::string name;
    std::map<std::string,Country> countries;
public:
    Continent(const std::string& name);
	Continent(const Continent& continent);
	std::string getName() const;
	void setName(const std::string& name);
    const std::map<std::string,Country> getCountries() const;
	void addCountry(Country country);
};
#endif // CONTINENT_H
