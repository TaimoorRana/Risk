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
	std::vector<Country*> countries;
public:
	Continent(const std::string& name, int score);
	std::string getName();
	void setName(const std::string& name);
	int getScore();
	void setScore(int score);
	std::vector<Country*> getCountries();
	void addCountry(Country* country);
};
#endif // LIB_CONTINENT_H
