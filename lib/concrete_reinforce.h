#ifndef CONCRETEREINFORCE_H
#define CONCRETEREINFORCE_H

#include "decorator.h"
/**
 * @brief The ConcreteReinforce class
 */
class ConcreteReinforce : public Decorator
{
public:
	/**
	 * @brief ConcreteReinforce
	 * @param c we copy the compenent so that it can be decorated
	 */
	ConcreteReinforce(Component *c);
	void log();
	~ConcreteReinforce();
	string getLog();
private:
	string reinforce = "\nreinforce phase\n";
};

#endif // CONCRETEREINFORCE_H
