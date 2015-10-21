#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>
#include <vector>
#include "country.h"

class Country; // forward declaration

class Continent {
private:
	std::string name = "";
	int reinforcement_bonus = 0;
	std::vector<Country*> countries = std::vector<Country*>();
public:
	Continent(const std::string& name, int reinforcement_bonus);
	Continent(const Continent& continent);
	std::string getName() const;
	void setName(const std::string& name);
	int getReinforcementBonus() const;
	void setReinforcementBonus(int reinforcement_bonus);
	std::vector<Country*>& getCountries();
	void addCountry(Country* country);
};
#endif // CONTINENT_H
