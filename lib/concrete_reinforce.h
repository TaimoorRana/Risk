#ifndef CONCRETEREINFORCE_H
#define CONCRETEREINFORCE_H

#include "decorator.h"
class ConcreteReinforce : public decorator
{
public:
	ConcreteReinforce();
	void log();

	string getLog();
private:
	string reinforce = "reinforce phase";
};

#endif // CONCRETEREINFORCE_H
