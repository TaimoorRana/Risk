#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>

class Continent {
private:
	std::string name = "";
	int reinforcementBonus = 0;
public:
	Continent() {};
	Continent(const std::string& name);
	Continent(const Continent& continent);
	std::string getName() const;
	void setName(const std::string& name);
	int getReinforcementBonus() const;
	void setReinforcementBonus(int bonus);
};
#endif // CONTINENT_H
