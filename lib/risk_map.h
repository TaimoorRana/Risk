#ifndef RISK_MAP
#define RISK_MAP

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <unordered_map>

#include "country.h"
#include "continent.h"
#include "graph_adt.h"
#include "player.h"
#include "observable.h"
#include "../gui/enum_savetype.h"

#include <cereal/types/string.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/xml.hpp>

#define MAP_PARSE_MODE_MAP 1
#define MAP_PARSE_MODE_CONTINENTS 2
#define MAP_PARSE_MODE_COUNTRIES 3

/**
 * @brief The RiskMap class which handles checking if countries are adjacent
 * adding and removing a player, adding and removing continents and also countries.
 */
class RiskMap : public Observable
{
private:
	std::unordered_map<std::string, Continent> continents;
	std::unordered_map<std::string, Country> countries;
	std::map<std::string, Player> players;
	SubGraphADT mapGraph;
	int numberOfCountries;
public:
	bool disableNotify = false;
	/**
	 * @brief RiskMap default constructor
	 */
	RiskMap();
	virtual ~RiskMap();
	/**
	 * @brief areCountriesAdjacent checks whether the countries are adjacent
	 * @param country_a
	 * @param country_b
	 * @return
	 */
	bool areCountriesAdjacent(const std::string& country_a, const std::string& country_b);
	/**
	 * @brief addCountry adds a country as a Country Object
	 * @param country
	 * @param continentName
	 * @return
	 */

	/**
	 * @brief renameCountry
	 * @param newname
	 * This will rename a given country
	 */
	void renameCountry(const std::string oldname, const std::string newname);

	Country* addCountry(const Country& country, const std::string& continentName);
	/**
	 * @brief addContinent adds a continet with the reinforcement bonus
	 * @param name
	 * @param reinforcementBonus
	 */
	void addContinent(const std::string& name, int reinforcementBonus);
	/**
	 * @brief addContinent adds a continent without the reinforcement bonus
	 * @param continent
	 */
	void addContinent(const Continent& continent);
	/**
	 * @brief remCountry removes a country
	 * @param country
	 */
	void remCountry(const Country& country);
	/**
	 * @brief addNeighbour adds a neighbour to a country
	 * @param country_a
	 * @param country_b
	 */
	void addNeighbour(const std::string& country_a, const std::string& country_b);
	/**
	 * @brief remNeighbour removes a neighbour
	 * @param country_a
	 * @param country_b
	 */
	void remNeighbour(const std::string& country_a, const std::string& country_b);
	/**
	 * @brief addPlayer adds a plyer
	 * @param player
	 */
	/**
	 * @brief addPlayer adds the player
	 * @param player
	 */
	Player* addPlayer(const Player& player);
	/**
	 * @brief getContinentOfCountry gets a continent pointer of the country string
	 * @param name_country
	 * @return
	 */
	Continent* getContinentOfCountry(const std::string& name_country);
	/**
	 * @brief getContinent pointer with the name of the continent
	 * @param name
	 * @return
	 */
	Continent* getContinentByName(const std::string& name);
	/**
	 * @brief getCountry gets the country pointer with the string name of the country
	 * @param name_country
	 * @return
	 */

	Country* getCountry(const std::string& name_country);

	/**
	 * @brief getCountriesInContinent gets a set of the countries in the continent
	 * @param name_continent
	 * @return
	 */
	string_set getCountriesInContinent(const std::string& name_continent);
	string_set getNeighbours(const std::string& name_country);
	Player* getPlayer(const std::string& playerName);
	const std::unordered_map<std::string, Continent>& getContinents() const;
	const std::unordered_map<std::string, Country>& getCountries() const;
	const std::map<std::string, Player>& getPlayers() const;

	void consolePrintListOfNeighbours(const std::string& name_country);
	void consolePrintListOfCountries(const std::string& name_continent);
	static RiskMap* load(const std::string& path);

	/**
	 * @brief parse
	 * This method parses a map file and then populates the map object with the contents retrieved.
	 * @param path
	 */
	void parse(const std::string& path);
	/**
	 * @brief save saves the map
	 * @param path
	 * @return
	 */

	static RiskMap* loadXML(std::string& path);
	bool save(SaveType t);
	bool saveMAP(std::string& path);
	bool saveXML(std::string& path);

	bool isEmpty();
	void clear();
	/**
	 * @brief validate validates the map based on the specififed rules
	 * @return
	 */
	bool validate();

	void isConnectedGraphHelper(std::unordered_map<const Country*, bool>& visited, Country* country, const std::string& limit_to);
	bool isConnectedGraph(const std::string& limit_to);

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("continents", this->continents), cereal::make_nvp("countries", this->countries), cereal::make_nvp("graph", this->mapGraph),cereal::make_nvp("players", this->players));
	}
};

#endif
