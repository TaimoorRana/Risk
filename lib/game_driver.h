#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H
#include <string>
#include <cereal/types/string.hpp>

#include "country.h"
#include "game_modes.h"
#include "observable.h"
#include "player.h"

/**
 * @brief The GameDriver class
 * Handles the ordering of the game  the players turn the number of reinforcements
 * calculating the number of armies placed and allowed to place
 */
class GameDriver: public Observable {
public:
	std::string getCurrentPlayerName() const;
	void setCurrentPlayerName(const std::string& name);

	Mode getCurrentMode() const;
	void setCurrentMode(const Mode& mode);

	/**
	 * @brief Perform an attack move on a country.
	 */
	void attackCountry(Country* attackerCountry, Country* defenderCountry);

	/**
	 * @brief calculateReinforcementArmies calculates the reinforcements for the player using the continents and countries
	 * that the player owns.
	 * @param p the player pointer
	 *
	 */
	void calculateReinforcementArmies(Player *p);

	/**
	 * @brief attackPhase
	 */
	void attackPhase();

	/**
	 * @brief implements reinforcePhase
	 */
	void reinforcePhase();

	/**
	 * @brief implements fortificationPhase
	 */
	void fortificationPhase();

	/**
	 * @brief implements endTurn
	 */
	void endTurn();

	/**
	 * @brief getInstance gets the singleton instance of the gamedriver
	 * @return
	 */
	static GameDriver* getInstance();

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("currentPlayerName", this->currentPlayerName), cereal::make_nvp("currentMode", this->currentMode));
	}

private:
	std::string currentPlayerName = "";
	Mode currentMode = REINFORCEMENTMODE;
};

#endif // GAMEDRIVER_H
