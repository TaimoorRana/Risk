#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>

class Continent {
private:
	std::string name;
public:
	Continent():name(""){}
	Continent(const std::string&);
	Continent(const Continent&);
	std::string getName() const;
};
#endif // CONTINENT_H
