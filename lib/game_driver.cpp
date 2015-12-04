#include <algorithm>
#include <random>
#include <string>
#include <time.h>
#include "ai/strategy.h"
#include "ai/random.h"
#include "ai/aggressive.h"
#include "ai/defensive.h"
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
	this->currentPlayerName = name;
	this->notifyObservers();
}

/**
 * @brief Ends the current phase, calling the next turn if it's the last phase.
 */
void GameDriver::endPhase() {
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "phase ended");

	Mode currentMode = this->getCurrentMode();
	if (currentMode == REINFORCEMENT) {
		this->setCurrentMode(ATTACK);
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "phase started");
		this->signalAI();
	}
	else if (currentMode == ATTACK) {
		// Hand a card to the attacker at the end of Attack mode
		this->handACardToWinner();

		this->setCurrentMode(FORTIFICATION);
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "phase started");
		this->signalAI();
	}
	else {
		this->nextTurn();
//        std::cout << "***************"<< this->getCurrentPlayerName() << std::endl;
//        if (this->getRiskMap()->getContinentsOwnedByPlayer(this->getCurrentPlayerName()).size() == 0)
//        {
//            std::cout << "********Player is DEAD!!!!!!" << std::endl;

//            this->endPhase();
//            this->endPhase();
//            this->endPhase();
//        }
	}
}

/**
 * @brief Moves to the next turn, setting the current player to the next one and resets the current mode to REINFORCEMENT
 */
void GameDriver::nextTurn() {
	this->recalculateReinforcements();
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "turn ended");

	auto iterator = this->map->getPlayers().find(this->getCurrentPlayerName());
	auto end = this->map->getPlayers().end();
	std::advance(iterator, 1);
	if (iterator == end) {
		iterator = this->map->getPlayers().begin();
	}
	this->setNotificationsEnabled(false);
	this->setCurrentPlayerName((*iterator).first);
	this->setCurrentMode(REINFORCEMENT);
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "turn started");
	this->setNotificationsEnabled(true);

	this->signalAI();

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
	this->currentMode = mode;
	this->notifyObservers();
}

/**
 * @brief Signals the AI to take their phase action.
 */
void GameDriver::signalAI() {
	// Our AI players will need signals now to take action.
	Player *player = map->getPlayer(this->getCurrentPlayerName());
	if (player->isHuman()) {
		return;
	}

	Strategy* strategy = this->getRandomStrategy();
	strategy->takeAction(this->currentMode);
	delete strategy;
}

bool GameDriver::reinforceCountry(Player* player, Country* country, int amount) {
	if (amount <= 0 || player->getReinforcements() < amount) {
		return false;
	}

	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "reinforced " + country->getName() + " with " + std::to_string(amount) + " armies");
	player->adjustReinforcements(-amount);
	country->addArmies(amount);

	return true;
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
			Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "gave player a card");
			map->updateCards(-1);
			player->updateCards(+1);
		}
		else
		{
			Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "could not give player a card: there are no more cards left in the deck");
		}
		player->setDidWinCountry(false); // reset the value for upcoming turn
	}
}

/**
 * @brief Perform an attack move on a country
 * @return boolean indicating if the user has won the game with this attack.
 */
bool GameDriver::attackCountry(Country* attackerCountry, Country* defenderCountry) {
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), " Attacking " + defenderCountry->getName() + " (" + defenderCountry->getPlayer() + ") from " + attackerCountry->getName());
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
			Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "defender rolled " + std::to_string(defenderDiceRolls[i]) + ", attacker rolled " + std::to_string(attackerDiceRolls[i]));
			if (attackerDiceRolls[i] > defenderDiceRolls[i]) {
				defenderLosses++;
			}
			else {
				attackerLosses++;
			}
		}

		// Remove soldiers lost from the battle
		attackerArmy -= attackerLosses;
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "attacker lost " + std::to_string(attackerLosses) + " armies");

		defenderArmy -= defenderLosses;
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "defender lost " + std::to_string(defenderLosses) + " armies");
	}

	if (defenderArmy <= 0) {
		// Attacker victorious: hand over ownership to the attacking player
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "attacker won!");
		Player* winner = this->map->getPlayer(attackerCountry->getPlayer());
		winner->adjustBattlesWon(1);
		winner->setDidWinCountry(true); // Temp value that indicates that the player has won a country
		Player* loser = this->map->getPlayer(defenderCountry->getPlayer());
		loser->adjustBattlesLost(1);

        // kick loser out of game
		if(map->getCountriesOwnedByPlayer(loser->getName()).size() <= 0 ){
            loser->died();
		}

        // Set to zero awaiting fortifiaction
        defenderCountry->setArmies(0);

        // AI doesn't go throught eh slider to fortify after attack
        if (!winner->isHuman()) {
            int armies = rand()%(attackerCountry->getArmies()-1)+1;
            this->fortifyCountry(attackerCountry, defenderCountry, armies);
        }

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
		Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "defender won!");
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
	Logger::getInstance()->logMessage(this->getCurrentPlayerName(), this->getCurrentMode(), "Fortifying country " + originCountry->getName() + " with " + std::to_string(armies) + " armies from " + destinationCountry->getName());
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
		// Check for continent bonuses
		for (auto &continentName : this->map->getContinentsOwnedByPlayer(player->getName())) {
			Continent* continent = this->map->getContinent(continentName);
			reinforcements += continent->getReinforcementBonus();
		}
		player->setReinforcements(reinforcements);
	}
}

/**
 * @brief Verify if a player has won the game
 */
bool GameDriver::hasWon(std::string playerName) {
	return this->map->getContinentsOwnedByPlayer(playerName).size() == this->map->getContinents().size();
}

/**
 * @brief Helper method to get a random strategy
 */
Strategy* GameDriver::getRandomStrategy() {
	Strategy* strategy = nullptr;

	int type = rand() % 3;
	if (type == 0) {
		strategy = new Defensive();

	}
	else if(type == 1) {
		strategy = new Aggressive();

	}
	else if (type == 2) {
		strategy = new Random();
	}

	return strategy;
}
