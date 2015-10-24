#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>
#include <set>
#include <unordered_map>
#include "country.h"

class Country; // forward declaration

class Continent {
private:
	std::string name;
    std::unordered_map<std::string,Country> countries;
public:
    Continent():name(""){}
    Continent(const std::string& name);
	Continent(const Continent& continent);
	std::string getName() const;
	void setName(const std::string& name);
    std::unordered_map<std::string,Country> getCountries() const;
    void addCountry(const std::string&);
};
#endif // CONTINENT_H
