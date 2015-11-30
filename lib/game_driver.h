#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H
#include <string>
#include <cereal/types/string.hpp>

#include "country.h"
#include "game_modes.h"
#include "observable.h"
#include "player.h"
#include "risk_map.h"

/**
 * @brief The GameDriver class
 * Handles the ordering of the game  the players turn the number of reinforcements
 * calculating the number of armies placed and allowed to place
 */
class GameDriver: public Observable {
public:
	virtual ~GameDriver() {};
	static GameDriver* getInstance();
	RiskMap* getRiskMap();
	void setRiskMap(RiskMap* map);

	std::string getCurrentPlayerName() const;
	void setCurrentPlayerName(const std::string& name);
	Mode getCurrentMode() const;
	void setCurrentMode(const Mode& mode);

	bool attackCountry(Country* attackerCountry, Country* defenderCountry);
	bool fortifyCountry(Country* originCountry, Country* destinationCountry, int armies);

	void recalculateReinforcements();

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("currentPlayerName", this->currentPlayerName), cereal::make_nvp("currentMode", this->currentMode));
	}

private:
	GameDriver() {}
	RiskMap* map = nullptr;
	std::string currentPlayerName = "";

	Mode currentMode = REINFORCEMENT;

};

#endif // GAMEDRIVER_H
