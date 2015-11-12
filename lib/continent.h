#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>
/**
 * @brief The Continent class holds the name and the number of reinforcement of a continent
 */
class Continent {
private:
	std::string name = "";
	int reinforcementBonus = 0;
public:
	/**
	 * @brief Continent
	 */
	Continent() {};
	/**
	 * @brief Continent witht the name of the continent
	 * @param name
	 */
	Continent(const std::string& name);
	/**
	 * @brief Continent copy constructor
	 * @param continent
	 */
	Continent(const Continent& continent);
	/**
	 * @brief getName returns the name of the continext
	 * @return
	 */
	std::string getName() const;
	/**
	 * @brief setName sets the name of the continent
	 * @param name
	 */
	void setName(const std::string& name);
	/**
	 * @brief getReinforcementBonus gets the number of reinforcements
	 * @return
	 */
	int getReinforcementBonus() const;
	/**
	 * @brief setReinforcementBonus sets the number of reinforcements
	 * @param bonus
	 */
	void setReinforcementBonus(int bonus);
};
#endif // CONTINENT_H
