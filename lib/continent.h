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
    Continent& operator = (const Continent&);
    std::string getNameContinent() const;
};
#endif // CONTINENT_H