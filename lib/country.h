#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

class Country {
private:

	std::string name_of_country;
	std::string name_of_player;
	int armies;
public:
	Country():name_of_country(""){}
	Country(const std::string&);
	Country(const std::string&, int);
	Country(const Country&);
	std::string getName() const;
	void setName(const std::string&);
	void setPlayer(const std::string&);
	std::string getPlayer();
	void setArmies(const int&);
	void removeArmies(const int&);
	void addArmies(const int&);
	int getArmies();
};
#endif // COUNTRY_H
