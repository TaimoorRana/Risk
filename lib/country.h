#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <cereal/types/string.hpp>
#include "observable.h"

/**
 * @brief The Country class extends observable has the player name the number of armies
 * on the country the postion of the country on the map, can set and get the number of armies
 * and the position.
 */

class Country : public Observable {
private:
	std::string name = "";
	std::string player = "";
	int armies = 0;
	int x = 0;
	int y = 0;

public:
	/**
	 * @brief Country
	 */
	Country() {};
	/**
	 * @brief Country
	 * @param name
	 */
	Country(const std::string& name);
	/**
	 * @brief Country
	 */
	Country(const Country&);
	/**
	 * @brief getName
	 * @return
	 */
	std::string getName() const;
	/**
	 * @brief setName
	 */
	void setName(const std::string&);
	/**
	 * @brief setPlayer
	 */
	void setPlayer(const std::string&);
	/**
	 * @brief getPlayer
	 * @return
	 */
	std::string getPlayer() const;
	/**
	 * @brief setArmies
	 */
	void setArmies(const int&);
	/**
	 * @brief removeArmies
	 */
	void removeArmies(const int&);
	/**
	 * @brief addArmies
	 */
	void addArmies(const int&);
	/**
	 * @brief getArmies
	 * @return
	 */
	int getArmies() const;
	/**
	 * @brief getPositionX
	 * @return
	 */
	int getPositionX() const;
	/**
	 * @brief setPositionX
	 * @param x
	 */
	void setPositionX(int x);
	/**
	 * @brief getPositionY
	 * @return
	 */
	int getPositionY() const;
	/**
	 * @brief setPositionY
	 * @param y
	 */
	void setPositionY(int y);

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("name", this->name), cereal::make_nvp("x", this->x), cereal::make_nvp("y", this->y), cereal::make_nvp("armies", this->armies), cereal::make_nvp("player", this->player));
	}
};
#endif // COUNTRY_H
