#include <algorithm>
#include "debug.h"
#include "librisk.h"
#include "logging/logger.h"
#include "game_driver.h"

GameDriver* GameDriver::getInstance() {
	static GameDriver* instance = nullptr;
	if (instance == nullptr) {
		instance = new GameDriver();
	}
	return instance;
}

/**
 * @brief Gets the map associated to this instance.
 */
RiskMap* GameDriver::getRiskMap() {
	return this->map;
}

/**
 * @brief Sets the map associated to this instance.
 */
void GameDriver::setRiskMap(RiskMap* map) {
	this->map = map;
}

/**
 * @brief Sets the name of the player whose turn is active
 */
void GameDriver::setCurrentPlayerName(const std::string& name) {
	Logger::getInstance()->logMessage(this->currentPlayerName, this->getCurrentMode(), "turn ended");
	this->currentPlayerName = name;
	Logger::getInstance()->logMessage(this->currentPlayerName, this->getCurrentMode(), "turn started");
	this->recalculateReinforcements();
	this->notifyObservers();
}

/**
 * @brief Gets the name of the player whose turn is active
 */
std::string GameDriver::getCurrentPlayerName() const {
	return this->currentPlayerName;
}

/**
 * @brief Sets the current game phase
 */
Mode GameDriver::getCurrentMode() const {
	return this->currentMode;
}

/**
 * @brief Sets the current game phase
 */
void GameDriver::setCurrentMode(const Mode& mode) {
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->currentMode, "phase ended");

    // Hand a card to the attacker at the end of Attack mode
    if (mode == FORTIFICATION)
    {
        handACardToWinner();
    }

    this->currentMode = mode;
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->currentMode, "phase started");
	this->notifyObservers();
}

/**
 * @brief GameDriver::handACardToWinner
 * @param mode
 */
void GameDriver::handACardToWinner()
{
    Player* player = map->getPlayer(currentPlayerName);
    if (player->getDidWinCountry() == true) // player must have won a country in their turn
    {
        if (map->getCards() > 0)
        {
            map->updateCards(-1);
            player->updateCards(+1);
        } else
        {
            std::cout << "No more cards left" << std::endl;
        }
        player->setDidWinCountry(false); // reset the value for upcoming turn
    }
}

/**
 * @brief Perform an attack move on a country
 */
bool GameDriver::attackCountry(Country* attackerCountry, Country* defenderCountry) {
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "Starting attack on " + defenderCountry->getName() + "[owned by " + defenderCountry->getPlayer() + "] from " + attackerCountry->getName());
	int attackerArmy = attackerCountry->getArmies();
	int defenderArmy = defenderCountry->getArmies();
	int attackerDiceCount = 0;
	int defenderDiceCount = 0;

	if (attackerArmy == 1 || attackerCountry->getPlayer() == defenderCountry->getPlayer()) {
		return false;
	}

	while (attackerArmy > 1 && defenderArmy > 0) {
		attackerDiceCount = attackerArmy > 3 ? 3 : attackerArmy - 1;
		defenderDiceCount = defenderArmy > 1 ? 2 : 1;
		std::vector<int> attackerDiceRolls = rollDice(attackerDiceCount);
		std::vector<int> defenderDiceRolls = rollDice(defenderDiceCount);

		int attackerLosses = 0;
		int defenderLosses = 0;

		// Compare attacker's highest to Defender's highest dice roll
		int dicesToCompare = std::min(attackerDiceRolls.size(), defenderDiceRolls.size());
		for (int i = 0; i < dicesToCompare; i++){
			debug("Defender rolled " + std::to_string(defenderDiceRolls[i]) + ", attacker rolled " + std::to_string(attackerDiceRolls[i]));
			if (attackerDiceRolls[i] > defenderDiceRolls[i]) {
				defenderLosses++;
			}
			else {
				attackerLosses++;
			}
		}

		// Remove soldiers lost from the battle
		attackerArmy -= attackerLosses;
		debug("Attacker lost " + std::to_string(attackerLosses) + " armies");

		defenderArmy -= defenderLosses;
		debug("Defender lost " + std::to_string(defenderLosses) + " armies");
	}

	if (defenderArmy <= 0) {
		// Attacker victorious: hand over ownership to the attacking player
		debug("Attacker won!");
		Player* winner = this->map->getPlayer(attackerCountry->getPlayer());
		winner->adjustBattlesWon(1);
        winner->setDidWinCountry(true); // Temp value that indicates that the player has won a country
		Player* loser = this->map->getPlayer(defenderCountry->getPlayer());
		loser->adjustBattlesLost(1);

		attackerCountry->setArmies(attackerArmy - 1);
		defenderCountry->setArmies(1);
		defenderCountry->setPlayer(attackerCountry->getPlayer());
		this->recalculateReinforcements();

        // check if defender lost all territories
        if (map->getCountriesOwnedByPlayer(loser->getName()).size() == 0)
        {
            // Winner takes all the loser's cards
            int loserCards = loser->getCards();
            winner->updateCards(loserCards);
            loser->updateCards(-loserCards);
        }
	}
	else {
		// Defender victorious: reconfigure armies
		debug("Defender won!");
		Player* winner = this->map->getPlayer(defenderCountry->getPlayer());
		winner->adjustBattlesWon(1);

		Player* loser = this->map->getPlayer(attackerCountry->getPlayer());
		loser->adjustBattlesLost(1);

		attackerCountry->setArmies(attackerArmy - 1);
		attackerCountry->setArmies(attackerArmy);
		defenderCountry->setArmies(defenderArmy);
	}
	return true;
}

/**
 * @brief Perform an fortify move on a country
 */
bool GameDriver::fortifyCountry(Country* originCountry, Country* destinationCountry, int armies) {
	if (originCountry->getArmies() - armies <= 0) {
		return false;
	}
	originCountry->removeArmies(armies);
	destinationCountry->addArmies(armies);
	return true;
}

void GameDriver::addCardsTradeReinforcements(int numArmies)
{
    Player* player = this->map->getPlayer(currentPlayerName);
    player->setReinforcements(player->getReinforcements()+numArmies);
}

void GameDriver::updatePlayerCards(int numCards)
{
    Player* player = this->map->getPlayer(currentPlayerName);
    player->updateCards(numCards);
    player->notifyObservers();
}

/**
 * @brief Adjusts each player's reinforcement count
 */
void GameDriver::recalculateReinforcements() {
	for (auto const &ent1: this->map->getPlayers()) {
		Player* player = this->map->getPlayer(ent1.first);
		// Players get reinfocements equal to their countries/3 (discard fractions),
		// down to a minimum of three reinforcements.
		int countryBonus = this->map->getCountriesOwnedByPlayer(player->getName()).size() / 3;
		int reinforcements = std::max(3, countryBonus);
		debug("player adding armied");
		// Check for continent bonuses
		for (auto &continentName : this->map->getContinentsOwnedByPlayer(player->getName())) {
			Continent* continent = this->map->getContinent(continentName);
			reinforcements += continent->getReinforcementBonus();
		}
		player->setReinforcements(reinforcements);
	}
}
