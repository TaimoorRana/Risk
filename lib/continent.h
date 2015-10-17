#ifndef LIB_CONTINENT_H
#define LIB_CONTINENT_H

#include <string>
#include <vector>
#include "country.h"

class Country; //forward declaration

class Continent {
private:
	std::string name;
	int score;
	std::vector<Country> countries;
public:
	Continent(const std::string& name, int score);
	Continent(const Continent& continent);
	std::string getName() const;
	void setName(const std::string& name);
	int getScore() const;
	void setScore(int score);
	const std::vector<Country> getCountries() const;
	void addCountry(Country country);
};
#endif // LIB_CONTINENT_H
