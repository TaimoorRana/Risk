#ifndef RISK_MAP
#define RISK_MAP

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>

#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/xml.hpp>

#include "country.h"
#include "continent.h"
#include "graph_adt.h"
#include "player.h"
#include "observable.h"
#include "../gui/enum_savetype.h"

#define MAP_PARSE_MODE_MAP 1
#define MAP_PARSE_MODE_CONTINENTS 2
#define MAP_PARSE_MODE_COUNTRIES 3

/**
 * @brief The RiskMap class encapsulates the state of a Risk board, keeping
 * track of the countries, continents and player relationships.
 */
class RiskMap : public Observable
{
private:
	std::map<std::string, Continent> continents;
	std::map<std::string, Country> countries;
	std::map<std::string, Player> players;
	SubGraphADT mapGraph;
public:
	bool disableNotify = false;
	/**
	 * @brief RiskMap default constructor
	 */
	RiskMap();
	virtual ~RiskMap();
	bool areCountriesAdjacent(const std::string& country_a, const std::string& country_b);
	void addContinent(const Continent& continent);
	Continent* getContinent(const std::string& name);
	string_set getCountriesInContinent(const std::string& continentName);

	Country* addCountry(const Country& country, const std::string& continentName);
	Country* getCountry(const std::string& countryName);
	void removeCountry(const Country& country);
	void renameCountry(const std::string oldName, const std::string newName);
	void addNeighbour(const std::string& country1, const std::string& country2);
	string_set getNeighbours(const std::string& countryName);
	bool areCountriesNeighbours(const std::string& country1, const std::string& country2);
	void removeNeighbour(const std::string& country1, const std::string& country2);
	Continent* getContinentOfCountry(const std::string& countryName);

	Player* addPlayer(const Player& player);
	Player* getPlayer(const std::string& playerName);
	string_set getCountriesOwnedByPlayer(const std::string& playerName);
	string_set getContinentsOwnedByPlayer(const std::string& playerName);

	const std::map<std::string, Continent>& getContinents() const;
	const std::map<std::string, Country>& getCountries() const;
	const std::map<std::string, Player>& getPlayers() const;

	void load(const std::string& path);
	void loadMap(const std::string& path);
	void loadXML(const std::string& path);
	bool save(SaveType t, std::string path);
	bool saveMap(const std::string& path);
	bool saveXML(const std::string& path);

	void clear();
	bool validate();

	void isConnectedGraphHelper(std::map<const Country*, bool>& visited, Country* country, const std::string& limitTo);
	bool isConnectedGraph(const std::string& limitTo);

	template<class Archive>
	void serialize(Archive& archive) {
		archive(cereal::make_nvp("continents", this->continents), cereal::make_nvp("countries", this->countries), cereal::make_nvp("graph", this->mapGraph),cereal::make_nvp("players", this->players));
	}
};

#endif
