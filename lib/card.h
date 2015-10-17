#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
	std::string name;

public:
	Card();
	Card(const Card& card);
	std::string getName();
	void setName(const std::string& name);
};
#endif // CARD_H
