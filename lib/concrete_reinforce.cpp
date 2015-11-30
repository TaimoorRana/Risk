#include "concrete_reinforce.h"

ConcreteReinforce::ConcreteReinforce(Component *c)
{
	component = c;
	log();
}

void ConcreteReinforce::log()
{
	logging += component->getLog() + reinforce;
}

ConcreteReinforce::~ConcreteReinforce()
{
	delete component;
}

string ConcreteReinforce::getLog()
{
	return logging;
}

