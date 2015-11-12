#include <vector>

#include "risk_map.h"
#include "debug.h"

RiskMap::RiskMap(){}
RiskMap::~RiskMap(){
	this->clear();
}

bool RiskMap::areCountriesAdjacent(const std::string& country_a, const std::string& country_b){
	return mapGraph.areAdjacent(country_a, country_b);
}

void RiskMap::addContinent(const std::string& name, int reinforcementBonus){
	if (continents.find(name) == continents.end()) {
		continents[name] = Continent(name);
	}
	this->notifyObservers();
}

void RiskMap::addContinent(const Continent& continent){
	continents[continent.getName()] = continent;
	this->notifyObservers();
}

Country* RiskMap::addCountry(const Country& country, const std::string& continentName){
	if (continents.find(continentName) == continents.end()) {
		continents[continentName] = Continent(continentName);
	}
	if (countries.find(country.getName()) == countries.end()) {
		countries[country.getName()] = country;
	}
	if (!mapGraph.insertNode(country.getName(), continentName))
		return nullptr;
	this->notifyObservers();
	return &this->countries[country.getName()];
}

void RiskMap::remCountry(const Country& country){
	countries.erase(country.getName());
	mapGraph.removeNode(country.getName());
	this->notifyObservers();
}

void RiskMap::addNeighbour(const std::string& country_a, const std::string& country_b){
	mapGraph.insertEdge(country_a, country_b);
	this->notifyObservers();
}

void RiskMap::remNeighbour(const std::string& country_a, const std::string& country_b){
	mapGraph.removeEdge(country_a, country_b);
	this->notifyObservers();
}

Player* RiskMap::addPlayer(const Player& player) {
	if (this->players.find(player.getName()) == this->players.end()) {
		this->players[player.getName()] = player;
	}
	this->notifyObservers();
	return &this->players[player.getName()];
}

Continent* RiskMap::getContinentOfCountry(const std::string& name_country){
	std::string name_continent(mapGraph.getSubgraphName(name_country));
	return &continents[name_continent];
}

Continent* RiskMap::getContinent(const std::string& name){
	return &this->continents[name];
}

Country* RiskMap::getCountry(const std::string& name_country){
	return &this->countries[name_country];
}

string_set RiskMap::getCountriesInContinent(const std::string& name_continent){
	return mapGraph.subgraphContents(name_continent);
}

string_set RiskMap::getNeighbours(const std::string& name_country){
	return mapGraph.incidentEdges(name_country);
}

Player* RiskMap::getPlayer(const std::string& playerName){
	return &this->players[playerName];
}

void RiskMap::consolePrintListOfNeighbours(const std::string& name_country){
	std::cout<<"Neighbours of: "<<name_country<<std::endl;
	string_set neighbours(getNeighbours(name_country));
	string_set::const_iterator c_iter = neighbours.begin();
	while (c_iter != neighbours.end()) {
		std::cout<<"\t\t\t"<<*c_iter<<std::endl;
		c_iter++;
	}
}

void RiskMap::consolePrintListOfCountries(const std::string& name_continent){
	std::cout<<"Countries in: "<<name_continent<<std::endl;
	string_set countriesInside(mapGraph.subgraphContents(name_continent));
	string_set::const_iterator c_iter = countriesInside.begin();
	while (c_iter != countriesInside.end() ){
		std::cout<<"\t\t"<< *c_iter<<std::endl;
		c_iter++;
	}
}

void RiskMap::parse(const std::string& path) {
	this->setNotificationsEnabled(false);
	this->clear();

	std::ifstream infile(path);
	std::string line;
	int mode = 0;

	while (std::getline(infile, line))
	{
		std::string debug_str("Read line: ");
		debug_str.append(line);
		debug(debug_str);
		// Windows prefers /r/n, but getline() breaks only on \n.
		if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

		// Set the mode for how we should process lines based on section headers
		if (line.compare("[Map]") == 0) {
			mode = MAP_PARSE_MODE_MAP;
			debug("  Parsing map metadata");
			continue;
		}
		if (line.compare("[Continents]") == 0) {
			mode = MAP_PARSE_MODE_CONTINENTS;
			debug("  Parsing continents");
			continue;
		}
		if (line.compare("[Territories]") == 0) {
			mode = MAP_PARSE_MODE_COUNTRIES;
			debug("  Parsing countries");
			continue;
		}

		// Process lines per the current mode.
		std::string item;
		std::stringstream line_stream(line);
		std::vector<std::string> values;
		if (mode == MAP_PARSE_MODE_MAP || line.length() == 0) {
			debug_str = "  Skipping: ";
			debug_str.append(line);
			debug(debug_str);
			continue;
		}
		else if (mode == MAP_PARSE_MODE_CONTINENTS) {
			while (std::getline(line_stream, item, '=')) {
				values.push_back(item);
			}
			debug_str = "  Adding continent: ";
			debug_str.append(values[0]);
			debug(debug_str);

			Continent continent(values[0]);
			continent.setReinforcementBonus(atoi(values[1].c_str()));
			this->addContinent(continent);
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			std::string continentName(values[3]);

			debug_str = "  Adding country: ";
			debug_str.append(values[0]);
			debug_str.append(" in continent ");
			debug_str.append(continentName);
			debug(debug_str);

			Country country(values[0]);
			country.setPositionX(atoi(values[1].c_str()));
			country.setPositionY(atoi(values[2].c_str()));
			country.setArmies(0);
			this->addCountry(country, continentName);
		}
		else {
			debug("Error parsing line: " + line);
			return;
		}
	}

	debug("Parsing file again to configure adjacencies");
	infile.clear();
	infile.seekg(0, std::ios_base::beg);
	while (std::getline(infile, line))
	{
		std::string debug_str("Read line: ");
		debug_str.append(line);
		debug(debug_str);
		// Windows prefers /r/n, but getline() breaks only on \n.
		if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

		// Set the mode for how we should process lines based on section headers
		if (line.compare("[Map]") == 0) {
			mode = MAP_PARSE_MODE_MAP;
			debug("  Parsing map metadata");
			continue;
		}
		if (line.compare("[Continents]") == 0) {
			mode = MAP_PARSE_MODE_CONTINENTS;
			debug("  Parsing continents");
			continue;
		}
		if (line.compare("[Territories]") == 0) {
			mode = MAP_PARSE_MODE_COUNTRIES;
			debug("  Parsing countries");
			continue;
		}

		// Process lines per the current mode.
		std::string item;
		std::stringstream line_stream(line);
		std::vector<std::string> values;
		if (mode != MAP_PARSE_MODE_COUNTRIES || line.length() == 0) {
			debug_str = "  Skipping: ";
			debug_str.append(line);
			debug(debug_str);
			continue;
		}
		else if (mode == MAP_PARSE_MODE_COUNTRIES) {
			while (std::getline(line_stream, item, ',')) {
				values.push_back(item);
			}
			Country* country = this->getCountry(values[0]);
			std::vector<std::string>::iterator iter;
			for (iter = values.begin() + 4; iter < values.end(); iter++) {
				Country* neighbour = this->getCountry(*iter);
				this->addNeighbour(country->getName(), neighbour->getName());

				debug_str = "  ";
				debug_str.append(country->getName());
				debug_str.append(" touches ");
				debug_str.append(neighbour->getName());
				debug(debug_str);
			}
		}
		else {
			debug("Error parsing line: " + line);
			return;
		}
	}

	debug("Finished parsing: " + path);
	this->setNotificationsEnabled(true);
}

RiskMap* RiskMap::load(const std::string& path) {
	struct stat buffer;
	bool exists = (stat (path.c_str(), &buffer) == 0);

	if (!exists) {
		return NULL;
	}

	RiskMap* map = new RiskMap();
	map->parse(path);
	return map;
}

bool RiskMap::save(const std::string& path) {
	std::string debug_str("Saving map file to ");
	debug_str.append(path);
	debug(debug_str);
	std::ofstream outfile(path, std::ios::out);
	if (!outfile.is_open()) {
		return false;
	}

	outfile << "[Continents]" << std::endl;
	for (auto const &ent1 : this->continents) {
		const Continent& continent = ent1.second;
		outfile << continent.getName() << "=" << continent.getReinforcementBonus() << std::endl;
	}
	outfile << std::endl;

	outfile << "[Territories]" << std::endl;
	for (auto const &ent1 : this->countries) {
		const Country& country = ent1.second;
		const Continent* continent = this->getContinentOfCountry(country.getName());
		outfile << country.getName() << "," << country.getPositionX() << "," << country.getPositionY() << "," << continent->getName();
		for (auto const &neighbour_country : this->getNeighbours(country.getName())) {
			outfile << "," << neighbour_country;
		}
		outfile << std::endl;
	}
	outfile << std::endl;

	outfile.close();
	return true;
}

void RiskMap::clear() {
	this->continents.clear();
	this->countries.clear();
	this->mapGraph = SubGraphADT();
	this->notifyObservers();
}

const std::unordered_map<std::string, Continent>& RiskMap::getContinents() const {
	return this->continents;
}
const std::unordered_map<std::string, Country>& RiskMap::getCountries() const {
	return this->countries;
}
const std::unordered_map<std::string, Player>& RiskMap::getPlayers() const {
	return this->players;
}

bool RiskMap::validate() {
	bool result;

	// Check all countries form a connected graph
	result = isConnectedGraph("");
	if (!result) {
		return false;
	}

	// Check each continent's countries are connected subgraphs
	for (auto const &ent1 : this->continents) {
		const Continent& continent = ent1.second;
		result = isConnectedGraph(continent.getName());
		if (!result) {
			return false;
		}
	}

	return true;
}

void RiskMap::isConnectedGraphHelper(std::unordered_map<const Country*, bool>& visited, Country* country, const std::string& limit_to) {
	if (limit_to.size() > 0 && this->getContinentOfCountry(country->getName())->getName().compare(limit_to) != 0) {
		return;
	}
	bool& was_visited = visited.at(country);
	if (was_visited) {
		return;
	}
	was_visited = true;

	for (auto const &neighbourName : this->getNeighbours(country->getName())) {
		Country* neighbour = this->getCountry(neighbourName);
		this->isConnectedGraphHelper(visited, neighbour, limit_to);
	}
}

bool RiskMap::isConnectedGraph(const std::string& limit_to) {
	std::unordered_map<const Country*, bool> visited = std::unordered_map<const Country*, bool>();
	for (auto const &ent1 : this->countries) {
		const Country& country = ent1.second;

		if (limit_to.size() > 0 && this->getContinentOfCountry(country.getName())->getName().compare(limit_to) != 0) {
			continue;
		}

		visited.insert(std::pair<const Country*, bool>(&country, false));
	}

	Country* country = NULL;
	if (limit_to.size() > 0) {
		country = this->getCountry(*this->getCountriesInContinent(limit_to).begin());
	}
	else {
		country = &this->countries.begin()->second;
	}
	this->isConnectedGraphHelper(visited, country, limit_to);

	for (auto const &ent1 : visited) {
		if (!ent1.second) {
			Country country = *ent1.first;
			debug("Country " + country.getName() + " is not connected.");
			return false;
		}
	}

	return true;
}

