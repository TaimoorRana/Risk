#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include "observable.h"

class Country : public Observable {
private:
	std::string name = "";
	std::string player = "";
	int armies = 0;
	int x = 0;
	int y = 0;
public:
	Country() {};
	Country(const std::string& name);
	Country(const std::string& name, int x, int y, int armies);
    Country(int x, int y);
	Country(const Country&);
	std::string getName() const;
	void setName(const std::string&);
	void setPlayer(const std::string&);
	std::string getPlayer() const;
	void setArmies(const int&);
	void removeArmies(const int&);
	void addArmies(const int&);
	int getArmies() const;
	int getPositionX() const;
	void setPositionX(int x);
	int getPositionY() const;
	void setPositionY(int y);
};
#endif // COUNTRY_H
