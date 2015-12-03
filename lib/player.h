#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include <cereal/types/string.hpp>
#include <cereal/types/set.hpp>

#include "observable.h"

class Player: public Observable {
protected:
	int reinforcements = 0; ///< The player's total reinforcement bonus at the start of their next turn
	int battleWon = 0; ///< Number of battles the user has won (either attacking or defending)
	int battleLost = 0; ///< Number of battles the user has lost (either attacking or defending)
	std::string name = "";
	bool alive = true;
	int cards = 0;
	bool didWinCountry = false;
	bool human = true;

public:
	Player() {}
	Player(std::string name);
	//Player(const Player& other);
	/**
	 * @brief getName
	 * @return name of the player
	 */
	std::string getName() const;

	/**
	 * @brief getCards
	 * @return The number of cards a player has
	 */
	int getCards();

	/**
	 * @brief Updates the number of cards the user has
	 */
	int updateCards(int numberOfCards);

	/**
	 * @brief didWinCountry
	 * @return If the user has won a country in the current turn if they're attacking
	 */
	bool getDidWinCountry();

	/**
	 * @brief setDidWinCountry
	 */
	void setDidWinCountry(bool value);

	/**
	 * @brief setBattlesWon sets battleWon value
	 * @param battleWon
	 */
	void setBattlesWon(const int &amount);

	/**
	 * @brief Adjusts the player's battles won counter
	 * @param amount amount to add (if positive) or subtract (if negative)
	 */
	void adjustBattlesWon(const int& amount);

	/**
	 * @brief getBattlesWon
	 * @return total battles won
	 */
	int getBattlesWon() const;

	/**
	 * @brief setBattlesWon sets battleWon value
	 * @param battleWon
	 */
	void setBattlesLost(const int &amount);

	/**
	 * @brief Adjusts the player's battles lost counter
	 * @param amount amount to add (if positive) or subtract (if negative)
	 */
	void adjustBattlesLost(const int& amount);

	/**
	 * @brief getBattlesWon
	 * @return total battles won
	 */
	int getBattlesLost() const;

	/**
	 * @brief setReinforcements
	 * @param amount
	 */
	void setReinforcements(const int& amount);

	/**
	 * @brief Adjusts the player's reinforcement count.
	 * @param amount amount to add (if positive) or subtract (if negative)
	 */
	void adjustReinforcements(const int& amount);

	/**
	 * @brief getReinforcements
	 */
	int getReinforcements() const;
	bool isHuman();
	void setHuman(bool human);

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("name", this->name), cereal::make_nvp("reinforcements", this->reinforcements), cereal::make_nvp("battleWon", this->battleWon), cereal::make_nvp("battleLost", this->battleLost), cereal::make_nvp("human", this->human), cereal::make_nvp("cards", this->cards), cereal::make_nvp("didWinCountry", this->didWinCountry));
	}

	void died();
	bool isAlive() const;
};
#endif // PLAYER_H
