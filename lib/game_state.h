#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>

#include "game_driver.h"
#include "risk_map.h"

/**
 * @brief The GameState class
 * Use the Builder pattern to facilitate loading an saving game state to/from
 * files.
 */
class GameState {
public:
	static bool load(std::string path, GameDriver* driver, RiskMap* map);
	static bool save(std::string path, GameDriver* driver, RiskMap* map);

	static RiskMap* buildMap(std::string path);
	static GameDriver* buildGameDriver(std::string path);
	static bool buildSaveFile(std::string path, GameDriver* driver, RiskMap* map);
};

#endif // GAMESTATE_H
