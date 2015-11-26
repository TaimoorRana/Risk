#ifndef CONCRETEREINFORCE_H
#define CONCRETEREINFORCE_H

#include "decorator.h"
class ConcreteReinforce : public Decorator
{
public:
	ConcreteReinforce(Component *c);
	void log();
	~ConcreteReinforce();
	string getLog();
private:
	string reinforce = "\nreinforce phase\n";
};

#endif // CONCRETEREINFORCE_H
